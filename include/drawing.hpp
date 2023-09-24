#pragma once

#include <SDL2/SDL.h>
#include <array>

namespace game_of_life
{

constexpr int32_t WORLD_SIZE = 500;

using world_t = std::array<std::array<bool, WORLD_SIZE>, WORLD_SIZE>;

void drawWorld(world_t const&, SDL_Renderer*);
SDL_Renderer* createRenderer();
void stopDrawing();

void drawWorld(world_t const& world, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int32_t y{}; y < WORLD_SIZE; ++y)
    {
        for (int32_t x{}; x < WORLD_SIZE; ++x)
        {
            if (!world[y][x]) continue;
            SDL_Rect point = {x, y, 1, 1};
            SDL_RenderFillRect(renderer, &point);
        }
    }
}

SDL_Renderer* createRenderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { exit(EXIT_FAILURE); }
    SDL_Window *win = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WORLD_SIZE, WORLD_SIZE, SDL_WINDOW_SHOWN);
    if (win == NULL) { exit(EXIT_FAILURE);}
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) { exit(EXIT_FAILURE); }
    return renderer;
}

void stopDrawing()
{
    SDL_Quit();
}

} // namespace game_of_life