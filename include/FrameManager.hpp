/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** FrameManager.hpp
*/

#pragma once

#include <chrono>
#include <optional>
#include <functional>

using namespace std::chrono_literals;

class FrameManager {
public:
    using Clock = std::chrono::system_clock;
    using Duration = std::chrono::duration<double>;
    using TimePoint = decltype(Clock::now());
private:
    static bool _highResFpsCounter;

    Duration _duration{0s};
    TimePoint _lastFrame{};
    TimePoint _lastSecond{};

    double _deltaTime{0};
    uint32_t _framerate{0};
    uint32_t _frameCounter{0};

    std::optional<std::function<void()>> _onSecondFunc{std::nullopt};
public:
    FrameManager() = default;

    uint32_t update() noexcept;
    void onSecond(const std::function<void()> &func) noexcept;

    [[nodiscard]] double getDeltaTime() const noexcept;
    [[nodiscard]] uint32_t getFramerate() const noexcept;

    static bool isHighResFpsCounter() noexcept;
    static void setHighResFpsCounter(bool highResFpsCounter) noexcept;
};
