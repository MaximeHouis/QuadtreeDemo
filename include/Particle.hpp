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
    static constexpr const auto MAX_SPEED = 275.f;
    static constexpr const auto GRAVITY = 9.81f;
    static constexpr const auto RADIUS = 2.5f;

    static bool _gravityEnabled;

    sf::CircleShape _shape;
    sf::Vector2f _speed;

    void _bounce(const sf::Vector2f &future) noexcept;

    static sf::Vector2f _intersectCollision(const sf::Vector2f &A, const sf::Vector2f &B) noexcept;
    static bool _isOutOfBounds(const sf::Vector2f &pos) noexcept;
public:
    Particle(float x, float y);

    template<typename T>
    explicit Particle(const sf::Vector2<T> &pos)
            : Particle{static_cast<float>(pos.x), static_cast<float>(pos.y)}
    {
    }

    void tick(float deltaTime);
    const sf::CircleShape &getShape() const noexcept;

    static void toggleGravity() noexcept;
    static bool isGravityEnabled() noexcept;
    static void setGravityEnabled(bool gravityEnabled) noexcept;
};
