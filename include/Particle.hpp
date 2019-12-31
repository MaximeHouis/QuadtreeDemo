/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Particle.hpp
*/

#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "Utils.hpp"

// Binary mask
#define CHECK_BOUNDARY(boundary, direction) (boundary & direction)

class Particle {
public:
    using EntityList = std::vector<const Particle *>;
private:
    enum Boundary : std::uint8_t {
        NONE = 0,
        UP = 1,
        RIGHT = 2,
        DOWN = 4,
        LEFT = 8,

        HORIZONTAL = UP | DOWN,
        VERTICAL = LEFT | RIGHT
    };

    static constexpr const auto MAX_SPEED = 275.f;
    static constexpr const auto GRAVITY = 9.81f;
    static constexpr const auto RADIUS = 2.5f;

    static bool _gravityEnabled;

    static sf::Vector2f _intersectCollision(Boundary bound, const sf::Vector2f &A, const sf::Vector2f &B) noexcept;
    static Boundary _isOutOfBounds(const sf::Vector2f &pos) noexcept;

    sf::CircleShape _shape;
    sf::Vector2f _speed;

    TimePoint _birthStamp{Clock::now()};

    mutable EntityList *_nearbyEntities{nullptr};

    void _bounce(Boundary bound) noexcept;
    Duration _lifetime() const noexcept;
public:
    Particle(float x, float y);

    template<typename T>
    explicit Particle(const sf::Vector2<T> &pos)
            : Particle{static_cast<float>(pos.x), static_cast<float>(pos.y)}
    {}

    Particle(const Particle &) = delete;
    Particle &operator=(const Particle &) = delete;

    void tick(float deltaTime);

    void setNearbyEntities(EntityList *nearbyEntities) const noexcept;
    EntityList *getNearbyEntities() const noexcept;
    const sf::CircleShape &getShape() const noexcept;

    static void toggleGravity() noexcept;
    static bool isGravityEnabled() noexcept;
    static void setGravityEnabled(bool gravityEnabled) noexcept;
};
