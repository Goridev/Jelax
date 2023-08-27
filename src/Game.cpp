#include "Game.hpp"

Game::Game(){}
Game::~Game(){}

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

    // backgroundTex = TextureManager::LoadTexture(DEFAULT_IMAGE_BACKGROUND_PATH, renderer);
    // playerTex = TextureManager::LoadTexture(DEFAULT_IMAGE_PLAYER_PATH, renderer);

    backgroundTexture = TextureManager::LoadTexture(DEFAULT_IMAGE_BACKGROUND_PATH, renderer);
    playerTexture = TextureManager::LoadTexture(DEFAULT_IMAGE_PLAYER_PATH, renderer);
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
            SDL_Log("KEYDOWN : %c (code : %d)", keysym.sym, keysym.scancode);
            break;
        case SDL_KEYUP:
            keysym = event.key.keysym;
            SDL_Log("KEYUP : %c (code : %d)", keysym.sym, keysym.scancode);
            break;
        default:
            break;
    }
}
void Game::update()
{
    count++;
    playerTexture->rect.h = 100;
    playerTexture->rect.w = 100;
    playerTexture->rect.x  = count;
    playerTexture->rect.y = DEFAULT_SCREEN_HEIGHT - 100;
    if(playerTexture->rect.x >= DEFAULT_SCREEN_WIDTH)
    {
        count = 0;
    }
    std::cout << count << std::endl;
}
void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture->texture, NULL, NULL);
    SDL_RenderCopy(renderer, playerTexture->texture, NULL, &playerTexture->rect);
    SDL_RenderCopy(renderer, fpsText->texture, NULL, &fpsText->rect);
    // SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}
void Game::clean()
{
    SDL_DestroyTexture(backgroundTexture->texture);
    SDL_DestroyTexture(playerTexture->texture);
    SDL_DestroyTexture(fpsText->texture);
    // SDL_DestroyTexture(fpsTexture);

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

void Game::renderTextFps(int fps)
{
    fpsText = TextureManager::LoadTextureText(
        DEFAULT_SCREEN_WIDTH,
        DEFAULT_FONT_FAMILLY_TTF_PATH, 
        DEFAULT_FONT_SIZE, 
        Utils::intToString(fps, " FPS"),
        textColor,
        renderer
    );
    // if(TTF_Init() == 0) {
    //     TTF_Font *font = TTF_OpenFont(DEFAULT_FONT_FAMILLY_TTF_PATH, DEFAULT_FONT_SIZE);
    //     SDL_Surface *surface = TTF_RenderText_Solid(font, Utils::intToString(fps, " FPS"), textColor);
    //     fpsTexture = SDL_CreateTextureFromSurface(renderer, surface);
    //     fpsRect.x = DEFAULT_SCREEN_WIDTH - 250;
    //     fpsRect.y = 150;
    //     fpsRect.w = surface->w;
    //     fpsRect.h = surface->h;
        
    //     SDL_FreeSurface(surface);
    //     TTF_Quit();
    // }
}