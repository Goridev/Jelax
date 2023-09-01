//Using SDL and standard IO
#include "Game.hpp"

Game *game = nullptr;

int main(int argc, char const *argv[])
{

    game = new Game();

    game->init(
        DEFAULT_TITLE,
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 
        DEFAULT_SCREEN_WIDTH, 
        DEFAULT_SCREEN_HEIGHT, 
        false
    );

    while(game->running()) {
        // Start FPS
        game->frameStart = SDL_GetTicks();

        game->updateTextFPS(game->frameTime);

        game->handleEvents();
        game->update();
        game->render();
        // Stop Fps
        game->frameTime = SDL_GetTicks() - game->frameStart;

        // Limit Frame Rate
        if(game->getFrameDelay() > game->frameTime)
        {
            SDL_Delay(game->getFrameDelay() - game->frameTime);
        }
    }

    game->clean();
    return 0;
}
