/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Quadtree.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include <atomic>
#include <optional>

#include <SFML/Graphics.hpp>

#include "Particle.hpp"

class Quadtree final {
public:
    static size_t _MaxUnits;
    static size_t _MaxDepth;

    using EntityList = Particle::EntityList;
private:
    struct Children {
        std::unique_ptr<Quadtree> nw{nullptr};
        std::unique_ptr<Quadtree> ne{nullptr};
        std::unique_ptr<Quadtree> se{nullptr};
        std::unique_ptr<Quadtree> sw{nullptr};
    };

    static std::atomic<size_t> _instanceCount;

    EntityList _entities{};
    std::unique_ptr<Children> _children{nullptr};

    sf::FloatRect _location;
    sf::RectangleShape _visual{};

    size_t _depth;

    void _split();
    void _purge(decltype(_entities) &purge);

    void _pushEntities(decltype(_entities) &vec) const noexcept;
    [[nodiscard]] decltype(_entities) _getAllEntities() const noexcept;
public:
    Quadtree(const sf::FloatRect &location, size_t depth);
    Quadtree(float x, float y, float w, float h, size_t depth);
    ~Quadtree();

    bool insert(const Particle *entity);
    void draw(sf::RenderWindow &window) const noexcept;
    void update();
    void clear();

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t count() const noexcept;
    [[nodiscard]] bool hasChildren() const noexcept;

    [[nodiscard]] static size_t getInstanceCount() noexcept;
};
