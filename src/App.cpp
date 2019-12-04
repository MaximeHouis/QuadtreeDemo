/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** App.cpp
*/

#include "App.hpp"

App::App()
        : _sfWin{sf::VideoMode{1600, 900}, "Quadtree Demo", sf::Style::Close}
{
    _font.loadFromFile("Assets/Fonts/Cascadia.ttf");

    _fpsCounter.setFont(_font);
    _fpsCounter.setFillColor(sf::Color::Yellow);
    _fpsCounter.setPosition(10, 10);
    _fpsCounter.setCharacterSize(21);

    _frameManager.onSecond([&] {
        _fpsCounter.setString(std::to_string(_frameManager.getFramerate()) + " fps");
    });
}

void App::run()
{
    while (_sfWin.isOpen()) {
        _pollEvents();
        _tick();
        _render();

        _deltaTime = _frameManager.update();
    }
}

void App::_pollEvents()
{
    while (_sfWin.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _sfWin.close();
    }
}

void App::_tick()
{
}

void App::_render()
{
    _sfWin.clear();

    _sfWin.draw(_fpsCounter);

    _sfWin.display();
}
