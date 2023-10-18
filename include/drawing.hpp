#pragma once

#include <SDL2/SDL.h>
#include <iostream>

int32_t WORLD_SIZE = 500;
SDL_Renderer *renderer;

void drawWorld(bool**);
SDL_Renderer* createRenderer();
void stopDrawing();

void drawWorld(bool** world)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int32_t y = 0; y < WORLD_SIZE; ++y)
    {
        for (int32_t x = 0; x < WORLD_SIZE; ++x)
        {
            if (!world[y][x]) continue;
            SDL_Rect point = {x, y, 1, 1};
            SDL_RenderFillRect(renderer, &point);
        }
    }

    SDL_RenderPresent(renderer);
}

SDL_Renderer* createRenderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { exit(EXIT_FAILURE); }
    SDL_Window *win = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WORLD_SIZE, WORLD_SIZE, SDL_WINDOW_SHOWN);
    if (win == NULL) { exit(EXIT_FAILURE);}
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (rend == NULL) { exit(EXIT_FAILURE); }
    return rend;
}

void stopDrawing()
{
    SDL_Quit();
}