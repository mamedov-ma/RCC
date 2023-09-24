#include "game_of_life.hpp"

using namespace game_of_life;

int main()
{
    SDL_Renderer *renderer = createRenderer();

    world_t currentWorld{};
    world_t updatedWorld{};

    generateWorld(currentWorld);
    drawWorld(currentWorld, renderer);

    while (true)
    {
        updateWorld(currentWorld, updatedWorld);
        drawWorld(updatedWorld, renderer);
        SDL_RenderPresent(renderer);
        updateWorld(updatedWorld, currentWorld);
        drawWorld(currentWorld, renderer);
        SDL_RenderPresent(renderer);

        // if there is no life in the world, stop simulation
        if (std::all_of(currentWorld.begin(), currentWorld.end(), [](std::array<bool, WORLD_SIZE> const& raw) {
            return std::none_of(raw.begin(), raw.end(), [](bool i) { return i; }); }) || currentWorld == updatedWorld) [[unlikely]] { break; }
    }

    stopDrawing();

    return 0;
}