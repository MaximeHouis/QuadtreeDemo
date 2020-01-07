/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Particle.cpp
*/

#include "App.hpp"
#include "Core/Particle.hpp"
#include "Utils/Utils.hpp"

bool Particle::GravityEnabled{false};
const sf::Vector2f Particle::NullVector{0, 0};

Particle::Particle(float x, float y)
{
    const auto angle = Random::range() * 2.0 * M_PI;
    const auto amplitude = std::sqrt(Random::range());
    const auto dx = static_cast<float>(amplitude * std::cos(angle));
    const auto dy = static_cast<float>(amplitude * std::sin(angle));

    _speed = sf::Vector2f{dx, dy};

    _shape.setRadius(_radius);
    _shape.setPosition(x, y);
    _shape.setOrigin(sf::Vector2f{_radius / 2.f, _radius / 2.f});
    _shape.setFillColor(sf::Color::Yellow);
}

void Particle::_bounceNearby()
{
    if (_nearbyEntities == nullptr || _lifetime() < 750ms)
        return;

    for (auto &near : *_nearbyEntities) {
        if (near == nullptr || near == this)
            continue;

        const auto dist = Utils::distance(_shape.getPosition(), near->_shape.getPosition());
        if (dist <= _radius + near->_radius) {
            // Credits: substitute541 - http://blogs.love2d.org/content/circle-collisions
            // Improved and tweaked for this program

            {
                const auto massDiff{_mass - near->_mass};
                const auto massTotal{_mass + near->_mass};
                const auto totalSpeed{sf::Vector2f{_speed.x - near->_speed.x,
                                                   _speed.y - near->_speed.y}};
                const auto newSpeedThis{sf::Vector2f{
                        (_speed.x * massDiff + (2.0f * near->_mass * near->_speed.x)) / massTotal,
                        (_speed.y * massDiff + (2.0f * near->_mass * near->_speed.y)) / massTotal}};
                const auto newSpeedNear{totalSpeed + newSpeedThis};

                this->_speed = newSpeedThis;
                near->_speed = newSpeedNear;
            }
            {
                const auto posThis{this->_shape.getPosition()};
                const auto posNear{near->_shape.getPosition()};
                const auto midpoint{sf::Vector2f{(posThis.x + posNear.x) / 2.f, (posThis.y + posNear.y) / 2.f}};
                const auto dist{Utils::distance(posThis, posNear)};

                this->_shape.setPosition(midpoint.x + this->_radius * (posThis.x - posNear.x) / dist,
                                         midpoint.y + this->_radius * (posThis.y - posNear.y) / dist);
                near->_shape.setPosition(midpoint.x + near->_radius * (posNear.x - posThis.x) / dist,
                                         midpoint.y + near->_radius * (posNear.y - posThis.y) / dist);
            }
        }
    }
}

void Particle::_bounceBoundaries(Boundary bound) noexcept
{
    if (CHECK_BOUNDARY(bound, VERTICAL))
        _speed.x *= -1.0;

    if (CHECK_BOUNDARY(bound, HORIZONTAL))
        _speed.y *= -1.0;

    // Limit bouncing off the ground, energy loss simulation.
    if (GravityEnabled && bound == DOWN)
        _speed.y *= Random::getDouble(0.55, 0.65);
}

/*
 * The future position is out of bounds.
 * We need to find the point where the particle intersects the outer bounds.
 */
sf::Vector2f Particle::_intersectCollision(Boundary bound, const sf::Vector2f &A, const sf::Vector2f &B,
                                           std::uint8_t depth) noexcept
{
    // Let A be the current position, B the future position (out of bounds),
    // C the right angle point from A and B,
    // D the right angle point on the corresponding axis,
    // Z the intersection point we are trying to find.

    sf::Vector2f C;
    sf::Vector2f D;

    if (CHECK_BOUNDARY(bound, HORIZONTAL)) {
        C = sf::Vector2f{A.x, B.y};
        D = sf::Vector2f{A.x, bound == UP ? _radius : App::WIN_H - _radius};
    } else {
        C = sf::Vector2f{B.x, A.y};
        D = sf::Vector2f{bound == LEFT ? _radius : App::WIN_W - _radius, A.y};
    }

    const auto AD = Utils::distance(A, D);
    const auto AC = Utils::distance(A, C);
    const auto CB = Utils::distance(B, C);
    const auto DZ = (CB / AC) * AD;
    // Simplified from std::tan(std::atan(CB / AC)) * AD

    sf::Vector2f future{};

    if (CHECK_BOUNDARY(bound, HORIZONTAL))
        future = sf::Vector2f{A.x + DZ, D.y};
    else
        future = sf::Vector2f{D.x, A.y + DZ};

    // Happens when adjusted position is colliding with another boundary.
    if (const auto boundary = _isOutOfBounds(future)) {
        if (depth != 0) {
            std::cerr << "Position is still out of bounds: " << boundary << A << B << future << '\n';
            return future;
        }
        future = _intersectCollision(boundary, A, future, depth + 1);
    }

    return future;
}

void Particle::tick(float deltaTime)
{
    if (GravityEnabled && _speed != NullVector)
        _speed.y += GRAVITY * deltaTime;

    _bounceNearby();

    const auto pos = _shape.getPosition();
    const auto moveVec = sf::Vector2f{_speed.x * MAX_SPEED * deltaTime, _speed.y * MAX_SPEED * deltaTime};
    auto future = pos + moveVec;

    if (const auto bound = _isOutOfBounds(future)) {
        _bounceBoundaries(bound);
        future = _intersectCollision(bound, pos, future);

        if (future.y == pos.y) // We are on the ground, reset speed.
            _speed = NullVector;
    }

    _shape.setPosition(future);
}

Particle::Boundary Particle::_isOutOfBounds(const sf::Vector2f &pos) noexcept
{
    if (pos.y - _radius < 0)
        return Boundary::UP;

    if (pos.x + _radius > App::WIN_W)
        return Boundary::RIGHT;

    if (pos.y + _radius > App::WIN_H)
        return Boundary::DOWN;

    if (pos.x - _radius < 0)
        return Boundary::LEFT;

    return Boundary::NONE;
}

Duration Particle::_lifetime() const noexcept
{
    return Duration{Clock::now() - _birthStamp};
}

void Particle::toggleGravity() noexcept
{
    GravityEnabled = !GravityEnabled;
}

bool Particle::isGravityEnabled() noexcept
{
    return GravityEnabled;
}

void Particle::setGravityEnabled(bool gravityEnabled) noexcept
{
    GravityEnabled = gravityEnabled;
}

void Particle::setNearbyEntities(EntityList *nearbyEntities) const noexcept
{
    _nearbyEntities = nearbyEntities;
}

Particle::EntityList *Particle::getNearbyEntities() const noexcept
{
    return _nearbyEntities;
}

const sf::CircleShape &Particle::getShape() const noexcept
{
    return _shape;
}
