/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Utils.hpp
*/

#pragma once

#include <cmath>
#include <chrono>
#include <iostream>

#include <SFML/System/Vector2.hpp>

using Clock = std::chrono::system_clock;
using Duration = std::chrono::duration<double>;
using TimePoint = decltype(Clock::now());

using namespace std::chrono_literals;

template<typename T>
std::ostream &operator<<(std::ostream &os, const sf::Vector2<T> &vec)
{
    return os << "[" << vec.x << ", " << vec.y << "]";
}

namespace Utils {
    template<typename T>
    auto distance(const sf::Vector2<T> &a, const sf::Vector2<T> &b) noexcept
    {
        return static_cast<T>(std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2)));
    }
}
