#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_Log("[Game] Systems initialized");


        window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_BORDERLESS);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(window && renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Log("[Game] Window created");
            SDL_Log("[Game] Renderer created");
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    SDL_Surface* tmpPlayerSurface = IMG_Load(DEFAULT_IMAGE_PLAYER_PATH);
    SDL_Surface* tmpBackgroundSurface = IMG_Load(DEFAULT_IMAGE_BACKGROUND_PATH);
    backgroundTex = SDL_CreateTextureFromSurface(renderer, tmpBackgroundSurface);
    playerTex = SDL_CreateTextureFromSurface(renderer, tmpPlayerSurface);

    createWidgetFPS();
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    SDL_Keysym keysym;

    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            keysym = event.key.keysym;
            SDL_Log("Touche enfoncée : %c (code : %d)", keysym.sym, keysym.scancode);
            break;
        case SDL_KEYUP:
            keysym = event.key.keysym;
            SDL_Log("Touche relâchée : %c (code : %d)", keysym.sym, keysym.scancode);
            break;
        default:
            break;
    }
}
void Game::update()
{
    count++;
    destPlayerRect.h = 100;
    destPlayerRect.w = 100;
    destPlayerRect.x  = count;
    if(destPlayerRect.x >= DEFAULT_SCREEN_WIDTH)
    {
        count = 0;
    }
}
void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTex, NULL, NULL);
    SDL_RenderCopy(renderer, playerTex, NULL, &destPlayerRect);
    SDL_RenderCopy(renderer, fpsTex, NULL, &fpsRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}
void Game::clean()
{
    SDL_DestroyTexture(backgroundTex);
    SDL_DestroyTexture(playerTex);
    SDL_DestroyTexture(fpsTex);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
    SDL_Log("[Game] cleaned");
}

bool Game::running()
{
    return isRunning;
}

int Game::getFps()
{
    return DEFAULT_FPS;
}

int Game::getFrameDelay()
{
    return 1000 / DEFAULT_FPS;
}

void Game::createWidgetFPS()
{
    if(TTF_Init() == 0) {
        TTF_Font *font = TTF_OpenFont(DEFAULT_FONT_FAMILLY_TTF_PATH, DEFAULT_FONT_SIZE);
        if (!font)
        {
            SDL_Log("Couldn't find/init open ttf font.");
        } else {
            std::string framerDelayString = std::to_string(frameTime).append(" FPS");
            char const *framerDelayPtr = framerDelayString.c_str();

            fpsSurface = TTF_RenderText_Solid(font, framerDelayPtr, textColor);
            fpsTex = SDL_CreateTextureFromSurface(renderer, fpsSurface);
            fpsRect.x = DEFAULT_SCREEN_WIDTH - 250; // Center horizontaly
            fpsRect.y = 150; // Center verticaly
            fpsRect.w = fpsSurface->w;
            fpsRect.h = fpsSurface->h;
            // After you create the texture you can release the surface memory allocation because we actually render the texture not the surface.
            TTF_Quit();
        }
    }
}

void Game::renderWidgetFPS()
{
    createWidgetFPS();
}