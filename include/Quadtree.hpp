/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Quadtree.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include <optional>

#include <SFML/Graphics.hpp>

#include "Particle.hpp"

class Quadtree {
public:
    static size_t _MaxUnits;
    static size_t _MaxDepth;

    using Entity = const Particle *;
private:
    struct Children {
        std::unique_ptr<Quadtree> nw{nullptr};
        std::unique_ptr<Quadtree> ne{nullptr};
        std::unique_ptr<Quadtree> se{nullptr};
        std::unique_ptr<Quadtree> sw{nullptr};
    };

    std::vector<Entity> _units{};
    std::unique_ptr<Children> _children{nullptr};

    sf::FloatRect _location;
    sf::RectangleShape _visual{};

    void _split();
public:
    explicit Quadtree(const sf::FloatRect &location);
    Quadtree(float x, float y, float w, float h);

    bool insert(Entity entity);
    void draw(sf::RenderWindow &window) const noexcept;

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t count() const noexcept;
    [[nodiscard]] bool hasChildren() const noexcept;
};
