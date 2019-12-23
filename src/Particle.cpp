/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Particle.cpp
*/

#include <App.hpp>
#include "Random.hpp"
#include "Particle.hpp"

bool Particle::_gravityEnabled{false};

Particle::Particle(float x, float y)
        : _shape{}, _speed{}
{
    const auto dx = static_cast<float>(Random::getDouble(-1, 1) * (Random::getBool() ? 1.0 : -1.0));
    const auto dy = static_cast<float>((1.0f - std::fabs(dx)) * (Random::getBool() ? 1.0 : -1.0));

    _speed = sf::Vector2f{dx, dy};

    const float radius = 2.5f;
    const sf::Vector2f origin{radius / 2.f, radius / 2.f};

    _shape.setRadius(radius);
    _shape.setOrigin(origin);
    _shape.setPosition(x, y);
    _shape.setFillColor(sf::Color::Yellow);
}

void Particle::_bounce() noexcept
{
    const auto pos = _shape.getPosition();

    if (pos.x < 0 || pos.x > App::WIN_W)
        _speed.x *= -1.0;

    if (pos.y < 0 || pos.y > App::WIN_H)
        _speed.y *= -1.0;

    // Limit bouncing off the ground, energy loss simulation.
    if (pos.y > App::WIN_H)
        _speed.y *= 2.0 / 3.0;
}

void Particle::tick(float deltaTime)
{
    if (_gravityEnabled) {
        _speed.y += GRAVITY * deltaTime;
    }

    sf::Vector2f moveVec{_speed.x * MAX_SPEED * deltaTime, _speed.y * MAX_SPEED * deltaTime};
    const auto pos = _shape.getPosition();
    const auto future = pos + moveVec;

    if (_isOutOfBounds(future)) {
        _bounce();
        moveVec = sf::Vector2f{_speed.x * MAX_SPEED * deltaTime, _speed.y * MAX_SPEED * deltaTime};
    }

    _shape.move(moveVec);
}

bool Particle::_isOutOfBounds(const sf::Vector2f &pos) noexcept
{
    return pos.x < 0 ||
           pos.y < 0 ||
           pos.x > App::WIN_W ||
           pos.y > App::WIN_H;
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
