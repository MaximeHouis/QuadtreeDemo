/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** FrameManager.cpp
*/

#include "FrameManager.hpp"

bool FrameManager::_highResFpsCounter{false};

uint32_t FrameManager::update() noexcept
{
    const auto timePoint = Clock::now();

    // Compute frame time
    _duration = timePoint - _lastFrame;
    _deltaTime = _duration.count();
    _lastFrame = timePoint;

    // Compute frame per seconds
    if (_highResFpsCounter) {
        _framerate = static_cast<decltype(_framerate)>(1.0 / _deltaTime);

        if (_onSecondFunc)
            _onSecondFunc.value()();
    } else {
        _duration = timePoint - _lastSecond;

        ++_frameCounter;
        if (_duration >= 1s) {
            _framerate = _frameCounter;
            _frameCounter = 0;
            _lastSecond = timePoint;

            if (_onSecondFunc)
                _onSecondFunc.value()();
        }
    }

    return _deltaTime;
}

void FrameManager::onSecond(const std::function<void()> &func) noexcept
{
    _onSecondFunc = func;
}

double FrameManager::getDeltaTime() const noexcept
{
    return _deltaTime;
}

uint32_t FrameManager::getFramerate() const noexcept
{
    return _framerate;
}

bool FrameManager::isHighResFpsCounter() noexcept
{
    return _highResFpsCounter;
}

void FrameManager::setHighResFpsCounter(bool highResFpsCounter) noexcept
{
    _highResFpsCounter = highResFpsCounter;
}
