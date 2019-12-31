/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Utils.hpp
*/

#pragma once

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
    float distance(const sf::Vector2f &a, const sf::Vector2f &b) noexcept;
}
