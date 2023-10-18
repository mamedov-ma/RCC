#pragma once

#include "drawing.hpp"

void generateWorld(bool**);
uint8_t toUint(bool**, int32_t const, int32_t const);
void updateCell(bool const, bool*, uint8_t const);
void updateWorld(bool**, bool**);
void app();

void generateWorld(bool** world)
{
    for (int32_t y = 0; y < WORLD_SIZE; ++y) { for (int32_t x = 0; x < WORLD_SIZE; ++x) { world[y][x] = rand() & 1; } }
}

uint8_t toUint(bool** currentWorld, int32_t const y, int32_t const x)
{
    if (x >= WORLD_SIZE || x < 0 || y >= WORLD_SIZE || y < 0) { return 0; }
    return currentWorld[y][x];
}

void updateCell(bool const currentCell, bool* updatedCell, uint8_t const counter)
{
    if (currentCell)
    {
        if (counter < 2 || counter > 3) { *updatedCell = false; }
        else { *updatedCell = true; }
    }
    else
    {
        if (counter >= 3) { *updatedCell = true; }
        else { *updatedCell = false; }
    }
}

void updateWorld(bool** currentWorld, bool** updatedWorld)
{
    uint8_t counter{};

    for (int32_t y = 0; y < WORLD_SIZE; ++y)
    {
        for (int32_t x = 0; x < WORLD_SIZE; ++x)
        {
            counter += toUint(currentWorld, y - 1, x - 1);
            counter += toUint(currentWorld, y - 1, x - 1);
            counter += toUint(currentWorld, y - 1, x - 1);
            counter += toUint(currentWorld, y, x - 1);
            counter += toUint(currentWorld, y, x + 1);
            counter += toUint(currentWorld, y + 1, x - 1);
            counter += toUint(currentWorld, y + 1, x);
            counter += toUint(currentWorld, y + 1, x + 1);
            updateCell(currentWorld[y][x], &updatedWorld[y][x], counter);
            counter = 0;
        }
    }
}
