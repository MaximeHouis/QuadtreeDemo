/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Particle.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

class Particle {
private:
    static constexpr const auto SPEED = 275.f;

    sf::CircleShape _shape;
    sf::Vector2f _dir;

    static bool _isOutOfBounds(const sf::Vector2f &pos) noexcept;

    void _bounce() noexcept;
public:
    Particle(float x, float y);

    template<typename T>
    explicit Particle(const sf::Vector2<T> &pos)
            : Particle{static_cast<float>(pos.x), static_cast<float>(pos.y)}
    {
    }

    void tick(float deltaTime);

    const sf::CircleShape &getShape() const noexcept;
};
