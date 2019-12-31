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
    static constexpr auto WIN_W{1000u};
    static constexpr auto WIN_H{WIN_W};
private:
    static constexpr auto PARTICLE_CLICK_COUNT{15};

    FrameManager _frameManager{};

    sf::RenderWindow _sfWin;
    sf::Event _event{};

    sf::Font _font{};
    sf::Text _dataText{};
    sf::Text _statusText{};

    std::vector<std::unique_ptr<Particle>> _particles{};
    Quadtree _quadtree{0, 0, WIN_W, WIN_H, 0};

    bool _freeze{false};
    bool _drawQuads{false};
    bool _vsync{true};
    bool _drawText{true};

    void _keyPressed(sf::Keyboard::Key code);
    void _pollEvents();
    void _tick();
    void _render();
    void _updateStatus();
public:
    App();

    void run();
};
