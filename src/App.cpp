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
    static const auto color = sf::Color::Yellow;    // Cannot be constexpr :c
    constexpr auto fontSize = 16;

    _sfWin.setVerticalSyncEnabled(_vsync);

    _font.loadFromFile("Assets/Fonts/Cascadia.ttf");

    _dataText.setFont(_font);
    _dataText.setCharacterSize(fontSize);
    _dataText.setFillColor(color);
    _dataText.setPosition(10, 10);

    _updateStatus();
    _statusText.setFont(_font);
    _statusText.setCharacterSize(fontSize);
    _statusText.setFillColor(color);
    _statusText.setPosition(10, WIN_H - _statusText.getGlobalBounds().height - _statusText.getLineSpacing() - 10);

    _frameManager.onSecond([&] {
        const auto quads = Quadtree::getInstanceCount();
        std::stringstream ss;

        ss <<
           _frameManager.getFramerate() << " fps\n" <<
           _particles.size() << " entities\n" <<
           quads << " quad" << (quads != 1 ? "s" : "");

        _dataText.setString(ss.str());
    });
}

void App::_updateStatus()
{
    std::stringstream ss;

    ss << std::boolalpha
       << "V-Sync: " << _vsync << '\n'
       << "Gravity: " << Particle::isGravityEnabled();

    _statusText.setString(ss.str());
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

        case sf::Keyboard::T:
            _drawText = !_drawText;
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

        case sf::Keyboard::V:
            _vsync = !_vsync;
            _sfWin.setVerticalSyncEnabled(_vsync);
            break;

        default:
            break;
    }

    _updateStatus();
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

            for (int i = 0; i < PARTICLE_CLICK_COUNT; ++i) {
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

    if (_drawText) {
        _sfWin.draw(_dataText);
        _sfWin.draw(_statusText);
    }

    _sfWin.display();
}
