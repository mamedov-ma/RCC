cmake_minimum_required(VERSION 3.22)
project(game-of-life)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic -lSDL2main -lSDL2")

find_package(SDL2 REQUIRED)

add_executable(GAME_OF_LIFE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app.c
)

target_include_directories(GAME_OF_LIFE PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(GAME_OF_LIFE PRIVATE SDL2)