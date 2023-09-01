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
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
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

    player = new GameObject(
        DEFAULT_IMAGE_PLAYER_PATH,
        new Size(64, 64),
        renderer
    ); 
    backgroundTexture = TextureManager::LoadTexture(DEFAULT_IMAGE_BACKGROUND_PATH, renderer);
    fpsText = TextureManager::LoadTextureText(
        DEFAULT_SCREEN_WIDTH,
        DEFAULT_FONT_FAMILLY_TTF_PATH, 
        DEFAULT_FONT_SIZE, 
        Utils::intToString(fps, TEXT_FPS),
        textColor,
        renderer
    );
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
    int playerPosX = count * 2;
    int playerPosY = DEFAULT_SCREEN_HEIGHT - 100;
    Position* playerPos = new Position(playerPosX,playerPosY);
    player->update(playerPos);
    // playerTexture->destRect->h = 100;
    // playerTexture->destRect->w = 100;
    // playerTexture->destRect->x  = count * 2;
    // playerTexture->destRect->y = DEFAULT_SCREEN_HEIGHT - 100;

    if(player->position->x >= DEFAULT_SCREEN_WIDTH)
    {
        count = 0;
    }
    
    fpsText = TextureManager::LoadTextureText(
        DEFAULT_SCREEN_WIDTH,
        DEFAULT_FONT_FAMILLY_TTF_PATH, 
        DEFAULT_FONT_SIZE, 
        Utils::intToString(frameTime, TEXT_FPS),
        textColor,
        renderer
    );
}
void Game::render()
{
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, backgroundTexture->texture, NULL, NULL);
    player->render();
    SDL_RenderCopy(renderer, fpsText->texture, NULL, fpsText->destRect);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}
void Game::clean()
{
    SDL_DestroyTexture(backgroundTexture->texture);
    player->clean();
    SDL_DestroyTexture(fpsText->texture);

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

void Game::updateTextFPS(int fps)
{
    
}