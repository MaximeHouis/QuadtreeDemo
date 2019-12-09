/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Quadtree.cpp
*/

#include <iostream>

#include "Quadtree.hpp"

size_t Quadtree::_MaxUnits{5};
size_t Quadtree::_MaxDepth{10};

Quadtree::Quadtree(const sf::FloatRect &location)
        : _location{location}
{
    _visual.setOutlineThickness(1.f);
    _visual.setOutlineColor(sf::Color::Yellow);
    _visual.setFillColor(sf::Color::Transparent);
    _visual.setPosition(_location.left, _location.top);
    _visual.setSize(sf::Vector2f{_location.width, _location.height});

//    std::cout << "New quad: " << location.left << ", " << location.top << ", " << location.width << ", " << location.height << std::endl;
}

Quadtree::Quadtree(float x, float y, float w, float h)
        : Quadtree(sf::FloatRect{x, y, w, h})
{
}

void Quadtree::_split()
{
    if (hasChildren())
        throw std::runtime_error("Already has children");

    const float newWidth = _location.width / 2.f;
    const float newHeight = _location.height / 2.f;
    const float x = _location.left;
    const float y = _location.top;

    _children = std::make_unique<Children>();
    _children->nw = std::make_unique<Quadtree>(x, y, newWidth, newHeight);
    _children->ne = std::make_unique<Quadtree>(x + newWidth, y, newWidth, newHeight);
    _children->se = std::make_unique<Quadtree>(x + newWidth, y + newHeight, newWidth, newHeight);
    _children->sw = std::make_unique<Quadtree>(x, y + newHeight, newWidth, newHeight);

    for (auto &unit : _units)
        insert(unit);

    _units.clear();
}

bool Quadtree::insert(Quadtree::Entity entity)
{
    if (!entity->getShape().getGlobalBounds().intersects(_location))
        return false;

    if (hasChildren()) {
        if (!_children->nw->insert(entity))
            if (!_children->ne->insert(entity))
                if (!_children->se->insert(entity))
                    if (!_children->sw->insert(entity))
                        throw std::runtime_error("Insertion failed");
        return true;
    }

    if (size() >= _MaxUnits) {
        _split();
        return insert(entity);
    }

    _units.push_back(entity);
    return true;
}

void Quadtree::draw(sf::RenderWindow &window) const noexcept
{
    if (hasChildren()) {
        _children->nw->draw(window);
        _children->ne->draw(window);
        _children->se->draw(window);
        _children->sw->draw(window);
    } else {
        window.draw(_visual);
    }
}

size_t Quadtree::size() const noexcept
{
    return std::count_if(_units.cbegin(), _units.cend(), [](const Particle *particle) {
        return particle != nullptr;
    });
}

size_t Quadtree::count() const noexcept
{
    if (hasChildren())
        return _children->nw->count() +
               _children->ne->count() +
               _children->se->count() +
               _children->sw->count();

    return size();
}

bool Quadtree::hasChildren() const noexcept
{
    return _children != nullptr;
}
