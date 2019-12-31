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
        src/FrameManager.cpp include/FrameManager.hpp
        src/Core/Particle.cpp include/Core/Particle.hpp
        src/Core/Quadtree.cpp include/Core/Quadtree.hpp
        src/Utils/Utils.cpp include/Utils/Utils.hpp
        src/Utils/Random.cpp include/Utils/Random.hpp
)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})
