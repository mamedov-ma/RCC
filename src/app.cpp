#include "../include/game_of_life.hpp"

void app()
{
    bool** currentWorld{};
    bool** updatedWorld{};

    generateWorld(currentWorld);
    drawWorld(currentWorld);

    while (true)
    {
        updateWorld(currentWorld, updatedWorld);
        drawWorld(updatedWorld);
        updateWorld(updatedWorld, currentWorld);
        drawWorld(currentWorld);
    }
}