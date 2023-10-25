#include "../include/game_of_life.h"
#include "../include/drawing.h"

SDL_Renderer *renderer;

SDL_Renderer* createRenderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { exit(EXIT_FAILURE); }
    SDL_Window *win = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WORLD_SIZE, WORLD_SIZE, SDL_WINDOW_SHOWN);
    if (win == NULL) { exit(EXIT_FAILURE);}
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (rend == NULL) { exit(EXIT_FAILURE); }
    return rend;
}

void drawWorld(bool world[WORLD_SIZE][WORLD_SIZE])
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y = 0; y < WORLD_SIZE; ++y)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            if (!world[y][x]) continue;
            SDL_Rect point = {x, y, 1, 1};
            SDL_RenderFillRect(renderer, &point);
        }
    }

    SDL_RenderPresent(renderer);
}

void stopDrawing()
{
    SDL_Quit();
}

int main()
{
    renderer = createRenderer();
    app();
    stopDrawing();
    return 0;
}