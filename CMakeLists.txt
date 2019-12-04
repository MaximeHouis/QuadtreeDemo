cmake_minimum_required(VERSION 3.12)
project(QuadtreeDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE off)

include_directories(include)
add_compile_options(-Wall -Wextra -Weffc++)
link_libraries(sfml-system sfml-window sfml-graphics)

add_executable(
        quad-demo
        src/Main.cpp
        src/App.cpp include/App.hpp
        src/Random.cpp include/Random.hpp
        src/FrameManager.cpp include/FrameManager.hpp
        src/Particle.cpp include/Particle.hpp)
