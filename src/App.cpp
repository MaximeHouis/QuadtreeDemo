/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** App.cpp
*/

#include <sstream>
#include <iostream>

#include "App.hpp"

App::App()
        : _sfWin{sf::VideoMode{WIN_W, WIN_H}, "Quadtree Demo", sf::Style::Close}
{
    _sfWin.setVerticalSyncEnabled(true);

    _font.loadFromFile("Assets/Fonts/Cascadia.ttf");

    _statsText.setFont(_font);
    _statsText.setFillColor(sf::Color::Yellow);
    _statsText.setPosition(10, 10);
    _statsText.setCharacterSize(21);

    _frameManager.onSecond([&] {
        const auto quads = Quadtree::getInstanceCount();
        std::stringstream ss;

        ss <<
           _frameManager.getFramerate() << " fps\n" <<
           _particles.size() << " entities\n" <<
           quads << " quad" << (quads != 1 ? "s" : "") << "\n" <<
           "Gravity: " << (Particle::isGravityEnabled() ? "on" : "off");

        _statsText.setString(ss.str());
    });
}

void App::run()
{
    while (_sfWin.isOpen()) {
        _pollEvents();
        _tick();
        _render();

        _frameManager.update();
    }
}

void App::_keyPressed(sf::Keyboard::Key code)
{
    switch (code) {
        case sf::Keyboard::Space:
            _quadtree.clear();
            _particles.clear();
            break;

        case sf::Keyboard::Q:
        case sf::Keyboard::Delete:
        case sf::Keyboard::Escape:
            _sfWin.close();
            break;

        case sf::Keyboard::F:
            _freeze = !_freeze;
            break;

        case sf::Keyboard::G:
            Particle::toggleGravity();
            break;

        case sf::Keyboard::H:
            _drawQuads = !_drawQuads;
            break;

        default:
            break;
    }
}

void App::_pollEvents()
{
    while (_sfWin.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _sfWin.close();

        if (_event.type == sf::Event::KeyPressed)
            _keyPressed(_event.key.code);

        if (_event.type == sf::Event::EventType::MouseButtonPressed) {
            const auto pos = sf::Mouse::getPosition(_sfWin);

            for (int i = 0; i < 30; ++i) {
                auto ptr = std::make_unique<Particle>(pos);

                _quadtree.insert(ptr.get());
                _particles.push_back(std::move(ptr));
            }
        }
    }
}

void App::_tick()
{
    _quadtree.update();

    if (_freeze)
        return;

    const auto slowmoFactor = sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? 0.5f : 1.f;
    const auto dt = static_cast<float>(_frameManager.getDeltaTime()) * slowmoFactor;

    for (auto &particle : _particles)
        particle->tick(dt);
}

void App::_render()
{
    _sfWin.clear();

    for (const auto &particle : _particles)
        _sfWin.draw(particle->getShape());

    if (_drawQuads)
        _quadtree.draw(_sfWin);
    _sfWin.draw(_statsText);

    _sfWin.display();
}
