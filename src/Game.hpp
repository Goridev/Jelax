#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "TextureManager.hpp"
#include "Utils.hpp"

#define DEFAULT_TITLE "JustRelax"
#define DEFAULT_SCREEN_WIDTH 1600
#define DEFAULT_SCREEN_HEIGHT 900

#define DEFAULT_FONT_FAMILLY_TTF_PATH "assets/fonts/Montserrat-Medium.ttf"
#define DEFAULT_FONT_SIZE 48

#define DEFAULT_IMAGE_PLAYER_PATH "assets/images/perso.png"
#define DEFAULT_IMAGE_BACKGROUND_PATH "assets/images/back_future.jpg"

#define DEFAULT_FPS 60

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    int getFps();
    int getFrameDelay();

    void renderTextFps(int fps);

    Uint32 frameStart;
    int frameTime;

private:
    int count;
    bool isRunning;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Color textColor = { 255, 255, 255, 255 };

    // SDL_Texture* backgroundTex;
    // SDL_Texture* playerTex;
    // SDL_Rect srcPlayerRect, destPlayerRect;
    // SDL_Texture *fpsTexture;
    // SDL_Rect fpsRect;

    Texture* backgroundTexture = new Texture();
    Texture* playerTexture = new Texture();
    Texture* fpsText = new Texture();
};

#endif