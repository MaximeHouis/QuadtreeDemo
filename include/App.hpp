/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** App.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "FrameManager.hpp"
#include "Core/Particle.hpp"
#include "Core/Quadtree.hpp"

class App final {
public:
    static constexpr auto WIN_W{1000u};
    static constexpr auto WIN_H{WIN_W};
private:
    static constexpr auto PARTICLE_CLICK_COUNT{150};

    FrameManager _frameManager{};

    sf::RenderWindow _sfWin;
    sf::Event _event{};

    sf::Font _font{};
    sf::Text _dataTxt{};
    sf::Text _statusTxt{};

    std::vector<std::unique_ptr<Particle>> _particles{};
    Quadtree _quadtree{0, 0, WIN_W, WIN_H, 0};

    bool _freeze{false};
    bool _drawQuads{false};
    bool _vsync{true};
    bool _drawText{true};

    void _updateStatus();
    void _mousePressed();
    void _keyPressed(sf::Keyboard::Key code);
    void _pollEvents();
    void _tick();
    void _render();
public:
    App();

    void run();
};
