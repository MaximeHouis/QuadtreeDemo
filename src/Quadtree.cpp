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

std::atomic<size_t> Quadtree::_instanceCount{0};

Quadtree::Quadtree(const sf::FloatRect &location, size_t depth)
        : _location{location}, _depth{depth}
{
    ++_instanceCount;

    _visual.setOutlineThickness(1.f);
    _visual.setOutlineColor(sf::Color::Yellow);
    _visual.setFillColor(sf::Color::Transparent);
    _visual.setPosition(_location.left, _location.top);
    _visual.setSize(sf::Vector2f{_location.width, _location.height});
}

Quadtree::Quadtree(float x, float y, float w, float h, size_t depth)
        : Quadtree(sf::FloatRect{x, y, w, h}, depth)
{
}

Quadtree::~Quadtree()
{
    --_instanceCount;
}

void Quadtree::_split()
{
    if (_depth >= _MaxDepth)
        return;

    if (hasChildren())
        throw std::runtime_error("Already has children");

    const float newWidth = _location.width / 2.f;
    const float newHeight = _location.height / 2.f;
    const float x = _location.left;
    const float y = _location.top;
    const auto newDepth = _depth + 1;

    _children = std::make_unique<Children>();
    _children->nw = std::make_unique<Quadtree>(x, y, newWidth, newHeight, newDepth);
    _children->ne = std::make_unique<Quadtree>(x + newWidth, y, newWidth, newHeight, newDepth);
    _children->se = std::make_unique<Quadtree>(x + newWidth, y + newHeight, newWidth, newHeight, newDepth);
    _children->sw = std::make_unique<Quadtree>(x, y + newHeight, newWidth, newHeight, newDepth);

    for (auto &unit : _entities)
        insert(unit);

    _entities.clear();
}

bool Quadtree::insert(const Particle *entity)
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

    _entities.push_back(entity);

    if (size() > _MaxUnits)
        _split();

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

void Quadtree::_purge(decltype(_entities) &purge)
{
    if (hasChildren()) {
        _children->nw->_purge(purge);
        _children->ne->_purge(purge);
        _children->se->_purge(purge);
        _children->sw->_purge(purge);

        if (count() <= _MaxUnits) {
            const auto childrenEntities = _getAllEntities();

            _children = nullptr;

            for (const auto &entity : childrenEntities)
                insert(entity);
        }
    } else {
        auto it = _entities.cbegin();

        while (it != _entities.cend()) {
            if (!(*it)->getShape().getGlobalBounds().intersects(_location)) {
                purge.push_back(*it);
                it = _entities.erase(it);
            } else {
                it++;
            }
        }
    }
}

void Quadtree::update()
{
    static decltype(_entities) purge{};

    purge.clear();
    _purge(purge);

    for (auto &item : purge)
        insert(item);
}

void Quadtree::clear()
{
    _entities.clear();
    _children = nullptr;
}

size_t Quadtree::size() const noexcept
{
    return std::count_if(_entities.cbegin(), _entities.cend(), [](const Particle *particle) {
        return particle != nullptr;
    });
}

void Quadtree::_pushEntities(decltype(_entities) &vec) const noexcept
{
    if (hasChildren()) {
        _children->nw->_pushEntities(vec);
        _children->ne->_pushEntities(vec);
        _children->se->_pushEntities(vec);
        _children->sw->_pushEntities(vec);
    } else {
        for (const auto &entity : _entities)
            vec.push_back(entity);
    }
}

decltype(Quadtree::_entities) Quadtree::_getAllEntities() const noexcept
{
    decltype(_entities) container{};

    _pushEntities(container);
    return container;
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

size_t Quadtree::getInstanceCount() noexcept
{
    return _instanceCount;
}
