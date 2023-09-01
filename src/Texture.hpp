#ifndef Texture_hpp
#define Texture_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Texture
{
    public:
        Texture(){};
        ~Texture(){};
        SDL_Texture* texture = nullptr;
        SDL_Rect* srcRect = nullptr;
        SDL_Rect* destRect = nullptr;
};

#endif