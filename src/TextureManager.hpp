#ifndef TextureManage_hpp
#define TextureManage_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Texture
{
    public:
        Texture(){};
        ~Texture(){};
        SDL_Texture* texture = nullptr;
        SDL_Rect rect;
};

class TextureManager
{
    public:
        static Texture* LoadTexture(const char* filePath, SDL_Renderer* renderer);
        static Texture* LoadTextureText(int screenWidth, const char* fontPath, int fontSize, const char* text, SDL_Color color, SDL_Renderer* renderer);
};

#endif