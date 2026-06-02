cmake_minimum_required(VERSION 3.10)
project(game_2048)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)


add_executable(game_2048
    src/main.cpp
    src/renderer.cpp
    src/game.cpp)
target_include_directories(game_2048 PRIVATE include/ ${SDL2_INCLUDE_DIRS})
target_link_libraries(game_2048 PRIVATE ${SDL2_LIBRARIES} SDL2_ttf)
