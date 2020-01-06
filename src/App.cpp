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
    constexpr auto margin = 10;

    _sfWin.setVerticalSyncEnabled(_vsync);

    _font.loadFromFile("Assets/Fonts/Cascadia.ttf");

    _dataTxt.setFont(_font);
    _dataTxt.setCharacterSize(fontSize);
    _dataTxt.setFillColor(color);
    _dataTxt.setPosition(margin, margin);

    _updateStatus();
    _statusTxt.setFont(_font);
    _statusTxt.setCharacterSize(fontSize);
    _statusTxt.setFillColor(color);
    _statusTxt.setPosition(margin, WIN_H - _statusTxt.getGlobalBounds().height - _statusTxt.getLineSpacing() - margin);

    _frameManager.onSecond([&] {
        const auto quads = Quadtree::getInstanceCount();
        const auto collisions = Particle::getCollisionCount();

        std::stringstream ss;
        ss <<
           _frameManager.getFramerate() << " fps\n" <<
           _particles.size() << " entities\n" <<
           quads << " quad" << (quads != 1 ? "s" : "") << '\n' <<
           collisions << " collision" << (collisions != 1 ? "s" : "") << '\n';

        _dataTxt.setString(ss.str());
    });
}

void App::_updateStatus()
{
    std::stringstream ss;

    ss << std::boolalpha
       << "V-Sync: " << _vsync << '\n'
       << "Gravity: " << Particle::isGravityEnabled();

    _statusTxt.setString(ss.str());
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

void App::_mousePressed()
{
    const auto pos = sf::Mouse::getPosition(_sfWin);

    for (int i = 0; i < PARTICLE_CLICK_COUNT; ++i) {
        auto ptr = std::make_unique<Particle>(pos);

        _quadtree.insert(ptr.get());
        _particles.push_back(std::move(ptr));
    }
}

void App::_pollEvents()
{
    while (_sfWin.pollEvent(_event)) {
        switch (_event.type) {
            case sf::Event::Closed:
                _sfWin.close();
                break;
            case sf::Event::KeyPressed:
                _keyPressed(_event.key.code);
                break;
            case sf::Event::MouseButtonPressed:
                _mousePressed();
                break;
            default:
                break;
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
        _sfWin.draw(_dataTxt);
        _sfWin.draw(_statusTxt);
    }

    _sfWin.display();
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
