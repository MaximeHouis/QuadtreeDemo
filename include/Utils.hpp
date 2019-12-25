/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Utils.hpp
*/

#pragma once

#include <iostream>

#include <SFML/System/Vector2.hpp>

template<typename T>
std::ostream &operator<<(std::ostream &os, const sf::Vector2<T> &vec)
{
    return os << "[" << vec.x << ", " << vec.y << "]";
}

namespace Utils {
    float distance(const sf::Vector2f &a, const sf::Vector2f &b) noexcept;
}
