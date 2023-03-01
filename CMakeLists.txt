cmake_minimum_required(VERSION 3.22)
set(CMAKE_OSX_ARCHITECTURES x86_64)
project(HelloSFML)

set(CMAKE_CXX_STANDARD 20)

add_executable(HelloSFML main.cpp Game.cpp Game.h Player.cpp Player.h Bullet.cpp Bullet.h)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)