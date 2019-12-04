/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** App.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Particle.hpp"
#include "FrameManager.hpp"

class App final {
public:
    static constexpr const auto WIN_W{1600u};
    static constexpr const auto WIN_H{900u};
private:
    FrameManager _frameManager{};

    sf::RenderWindow _sfWin;
    sf::Event _event{};

    sf::Font _font{};
    sf::Text _fpsCounter{};
    sf::Text _entCount{};

    std::vector<Particle> _particles{};

    void _pollEvents();
    void _tick();
    void _render();
public:
    App();

    void run();
};
