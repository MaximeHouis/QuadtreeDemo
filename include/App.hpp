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
#include "Quadtree.hpp"

class App final {
public:
    static constexpr const auto WIN_W{1000u};
    static constexpr const auto WIN_H{1000u};
private:
    FrameManager _frameManager{};

    sf::RenderWindow _sfWin;
    sf::Event _event{};

    sf::Font _font{};
    sf::Text _statsText{};

    std::vector<std::unique_ptr<Particle>> _particles{};
    Quadtree _quadtree{0, 0, WIN_W, WIN_H, 0};

    bool _freeze{false};
    bool _drawQuads{true};

    void _keyPressed(sf::Keyboard::Key code);
    void _pollEvents();
    void _tick();
    void _render();
public:
    App();

    void run();
};
