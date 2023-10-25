#include "../include/game_of_life.h"

void generateWorld(bool world[WORLD_SIZE][WORLD_SIZE])
{
    for (int y = 0; y < WORLD_SIZE; ++y) { for (int x = 0; x < WORLD_SIZE; ++x) { world[y][x] = rand() & 1; } }
}

int toUint(bool currentWorld[WORLD_SIZE][WORLD_SIZE], int const y, int const x)
{
    if (x >= WORLD_SIZE || x < 0 || y >= WORLD_SIZE || y < 0) { return 0; }
    return currentWorld[y][x];
}

void updateCell(bool const currentCell, bool* updatedCell, int const counter)
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

void updateWorld(bool currentWorld[WORLD_SIZE][WORLD_SIZE], bool updatedWorld[WORLD_SIZE][WORLD_SIZE])
{
    int counter = 0;

    for (int y = 0; y < WORLD_SIZE; ++y)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
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

void app()
{
    bool currentWorld[WORLD_SIZE][WORLD_SIZE];
    bool updatedWorld[WORLD_SIZE][WORLD_SIZE];

    generateWorld(currentWorld);
    drawWorld(currentWorld);

    while (true)
    {
        bool equal = true;
        updateWorld(currentWorld, updatedWorld);
        drawWorld(updatedWorld);
        updateWorld(updatedWorld, currentWorld);
        drawWorld(currentWorld);

        for (int y = 0; y < WORLD_SIZE; ++y)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                if (currentWorld[y][x] != updatedWorld[y][x]) { equal = false; }
            }
        }
        if (equal) { return; }
    }
}