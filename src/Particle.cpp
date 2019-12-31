/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Particle.cpp
*/

#include "App.hpp"
#include "Utils.hpp"
#include "Random.hpp"
#include "Particle.hpp"

bool Particle::_gravityEnabled{false};

Particle::Particle(float x, float y)
        : _shape{}, _speed{}
{
    const auto angle = Random::range() * 2.0 * M_PI;
    const auto amplitude = std::sqrt(Random::range());
    const auto dx = static_cast<float>(amplitude * std::cos(angle));
    const auto dy = static_cast<float>(amplitude * std::sin(angle));

    _speed = sf::Vector2f{dx, dy};

    _shape.setRadius(RADIUS);
    _shape.setPosition(x, y);
    _shape.setOrigin(sf::Vector2f{RADIUS / 2.f, RADIUS / 2.f});
    _shape.setFillColor(sf::Color::Yellow);
}

/*
 * The future position is out of bounds.
 * We need to find the point where the particle intersects the outer bounds.
 */
sf::Vector2f Particle::_intersectCollision(Boundary bound, const sf::Vector2f &A, const sf::Vector2f &B) noexcept
{
    // Let A be the current position, B the future position (out of bounds),
    // C the right angle point from A and B,
    // D the right angle point on the corresponding axis,
    // Z the intersection point we are trying to find.

    sf::Vector2f C;
    sf::Vector2f D;

    if (CHECK_BOUNDARY(bound, HORIZONTAL)) {
        C = sf::Vector2f{A.x, B.y};
        D = sf::Vector2f{A.x, bound == UP ? RADIUS : App::WIN_H - RADIUS};
    } else {
        C = sf::Vector2f{B.x, A.y};
        D = sf::Vector2f{bound == LEFT ? RADIUS : App::WIN_W - RADIUS, A.y};
    }

    const auto AD = Utils::distance(A, D);
    const auto AC = Utils::distance(A, C);
    const auto CB = Utils::distance(B, C);
    const auto DZ = (CB / AC) * AD;         // Simplified from std::tan(std::atan(CB / AC)) * AD

    if (CHECK_BOUNDARY(bound, HORIZONTAL))
        return sf::Vector2f{A.x + DZ, D.y};
    else
        return sf::Vector2f{D.x, A.y + DZ};
}

void Particle::_bounce(Boundary bound) noexcept
{
    if (CHECK_BOUNDARY(bound, VERTICAL))
        _speed.x *= -1.0;

    if (CHECK_BOUNDARY(bound, HORIZONTAL))
        _speed.y *= -1.0;

    // Limit bouncing off the ground, energy loss simulation.
    if (_gravityEnabled && bound == DOWN)
        _speed.y *= 0.575;
}

void Particle::tick(float deltaTime)
{
    if (_gravityEnabled)
        _speed.y += GRAVITY * deltaTime;

    const auto pos = _shape.getPosition();
    const auto moveVec = sf::Vector2f{_speed.x * MAX_SPEED * deltaTime, _speed.y * MAX_SPEED * deltaTime};
    auto future = pos + moveVec;

    if (const auto bound = _isOutOfBounds(future)) {
        _bounce(bound);
        future = _intersectCollision(bound, pos, future);
    }

    _shape.setPosition(future);
}

Particle::Boundary Particle::_isOutOfBounds(const sf::Vector2f &pos) noexcept
{
    if (pos.y - RADIUS < 0)
        return Boundary::UP;

    if (pos.x + RADIUS > App::WIN_W)
        return Boundary::RIGHT;

    if (pos.y + RADIUS > App::WIN_H)
        return Boundary::DOWN;

    if (pos.x - RADIUS < 0)
        return Boundary::LEFT;

    return Boundary::NONE;
}

Duration Particle::_lifetime() const noexcept
{
    return Duration{Clock::now() - _birthStamp};
}

void Particle::toggleGravity() noexcept
{
    _gravityEnabled = !_gravityEnabled;
}

bool Particle::isGravityEnabled() noexcept
{
    return _gravityEnabled;
}

void Particle::setGravityEnabled(bool gravityEnabled) noexcept
{
    _gravityEnabled = gravityEnabled;
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
