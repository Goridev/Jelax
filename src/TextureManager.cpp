#include "TextureManager.hpp"

Texture* TextureManager::LoadTexture(const char* filePath, SDL_Renderer* renderer)
{
    Texture* tex = new Texture();
    SDL_Surface* surface = IMG_Load(filePath);
    tex->destRect = new SDL_Rect();
    tex->srcRect = new SDL_Rect();
    tex->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}

Texture* TextureManager::LoadTextureText(int screenWidth, const char* fontPath, int fontSize, const char* text, SDL_Color color, SDL_Renderer* renderer)
{
    TTF_Init();
    Texture* tex = new Texture();
    tex->destRect = new SDL_Rect();
    tex->srcRect = new SDL_Rect();

    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, color);
    tex->texture = SDL_CreateTextureFromSurface(renderer, surface);

    tex->destRect->x = screenWidth - 250;
    tex->destRect->y = 150;
    tex->destRect->w = surface->w;
    tex->destRect->h = surface->h;

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return tex;
}