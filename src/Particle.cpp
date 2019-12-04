/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Particle.cpp
*/

#include <App.hpp>
#include "Random.hpp"
#include "Particle.hpp"

Particle::Particle(float x, float y)
        : _shape{}, _dir{}
{
    const auto dx = static_cast<float>(Random::getDouble(-1, 1) * (Random::getBool() ? 1 : -1));
    const auto dy = static_cast<float>((1.0f - std::fabs(dx)) * (float) (Random::getBool() ? 1 : -1));

    _dir = sf::Vector2f{dx, dy};

    const float radius = 5;
    const sf::Vector2f origin{radius / 2.f, radius / 2.f};

    _shape.setRadius(5);
    _shape.setOrigin(origin);
    _shape.setPosition(x, y);
    _shape.setFillColor(sf::Color::Yellow);
}

void Particle::tick(float deltaTime)
{
    const sf::Vector2f moveVec{_dir.x * SPEED * deltaTime, _dir.y * SPEED * deltaTime};
    const auto pos = _shape.getPosition();
    const auto future = pos + moveVec;

    if (_isOutOfBounds(future))
        _bounce();
    else
        _shape.move(moveVec);
}

void Particle::_bounce() noexcept
{
    const auto pos = _shape.getPosition();

    if (pos.x < 0 || pos.x > App::WIN_W)
        _dir.x *= -1.0;

    if (pos.y < 0 || pos.y > App::WIN_H)
        _dir.x *= -1.0;
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
