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
    const auto dx = static_cast<float>(Random::getDouble(-1, 1) * (Random::getBool() ? 1.0 : -1.0));
    const auto dy = static_cast<float>((1.0f - std::fabs(dx)) * (Random::getBool() ? 1.0 : -1.0));

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

    if (bound & HORIZONTAL) {
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

    if (bound & HORIZONTAL)
        return sf::Vector2f{A.x + DZ, D.y};
    else
        return sf::Vector2f{D.x, A.y + DZ};
}

void Particle::_bounce(Boundary bound) noexcept
{
    if (bound & VERTICAL)
        _speed.x *= -1.0;

    if (bound & HORIZONTAL)
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
    auto moveVec = sf::Vector2f{_speed.x * MAX_SPEED * deltaTime, _speed.y * MAX_SPEED * deltaTime};
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

const sf::CircleShape &Particle::getShape() const noexcept
{
    return _shape;
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
