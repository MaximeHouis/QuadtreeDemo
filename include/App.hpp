/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** App.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "FrameManager.hpp"

class App final {
public:

private:
    FrameManager _frameManager{};

    sf::RenderWindow _sfWin;
    sf::Event _event{};

    sf::Font _font{};
    sf::Text _fpsCounter{};

    decltype(std::declval<FrameManager>().getDeltaTime()) _deltaTime{};

    void _pollEvents();
    void _tick();
    void _render();
public:
    App();

    void run();
};
