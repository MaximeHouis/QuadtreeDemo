/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Utils.cpp
*/

#include <cmath>

#include "Utils/Utils.hpp"

namespace Utils {
    float distance(const sf::Vector2f &a, const sf::Vector2f &b) noexcept
    {
        return static_cast<float>(std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2)));
    }
}
