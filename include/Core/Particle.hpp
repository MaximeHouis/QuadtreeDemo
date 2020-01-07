/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Particle.hpp
*/

#pragma once

#include <cmath>
#include <atomic>

#include <SFML/Graphics.hpp>

#include "Utils/Utils.hpp"
#include "Utils/Random.hpp"

class Particle final {
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

    static constexpr const auto GRAVITY{9.81f};
    static constexpr const auto MAX_SPEED{275.f};

    static bool GravityEnabled;
    static const sf::Vector2f NullVector;

    static constexpr inline auto CHECK_BOUNDARY(Boundary boundary, Boundary direction)
    {
        return boundary & direction;
    }

    // Let's pretend the mass is the area of the circle
    const float _radius{static_cast<float>(Random::getDouble(2.5, 5.0))};
    const float _mass{static_cast<float>(M_PI * std::pow(_radius, 2))};

    // TODO: Only _nearbyEntities should be mutable.
    mutable EntityList *_nearbyEntities{nullptr};
    mutable sf::Vector2f _speed{};
    mutable sf::CircleShape _shape{};

    TimePoint _birthStamp{Clock::now()};

    Duration _lifetime() const noexcept;
    void _bounceNearby();
    void _bounceBoundaries(Boundary bound) noexcept;
    sf::Vector2f _intersectCollision(Boundary bound, const sf::Vector2f &A, const sf::Vector2f &B,
                                     std::uint8_t depth = 0) noexcept;
    Boundary _isOutOfBounds(const sf::Vector2f &pos) noexcept;
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
