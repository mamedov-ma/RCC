#pragma once

#include "drawing.hpp"

#include <random>
#include <algorithm>

namespace game_of_life
{

void generateWorld(world_t&) noexcept;
uint8_t toUint(world_t const&, int32_t const, int32_t const) noexcept;
void updateCell(bool const, bool&, uint8_t const) noexcept;
void updateWorld(world_t const&, world_t&) noexcept;


void generateWorld(world_t& world) noexcept
{
    std::mt19937 gen;
    std::bernoulli_distribution dist;
    for(auto& raw: world) { std::ranges::generate(raw, [&]() { return dist(gen); }); };
}

uint8_t toUint(world_t const& currentWorld, int32_t const y, int32_t const x) noexcept
{
    if (x >= WORLD_SIZE || x < 0 || y >= WORLD_SIZE || y < 0) [[unlikely]] { return 0; }
    return currentWorld[y][x];
}

void updateCell(bool const currentCell, bool& updatedCell, uint8_t const counter) noexcept
{
    if (currentCell)
    {
        if (counter < 2 || counter > 3) { updatedCell = false; }
        else { updatedCell = true; }
    }
    else
    {
        if (counter >= 3) { updatedCell = true; }
        else { updatedCell = false; }
    }
}

void updateWorld(world_t const& currentWorld, world_t& updatedWorld) noexcept
{
    uint8_t counter{};

    for (int32_t y{}; y < WORLD_SIZE; ++y)
    {
        for (int32_t x{}; x < WORLD_SIZE; ++x)
        {
            counter += toUint(currentWorld, y - 1, x - 1);
            counter += toUint(currentWorld, y - 1, x - 1);
            counter += toUint(currentWorld, y - 1, x - 1);
            counter += toUint(currentWorld, y, x - 1);
            counter += toUint(currentWorld, y, x + 1);
            counter += toUint(currentWorld, y + 1, x - 1);
            counter += toUint(currentWorld, y + 1, x);
            counter += toUint(currentWorld, y + 1, x + 1);
            updateCell(currentWorld[y][x], updatedWorld[y][x], counter);
            counter = 0;
        }
    }
}

} // namespace game_of_life
