#include "TextureManager.hpp"

Texture* TextureManager::LoadTexture(const char* filePath, SDL_Renderer* renderer)
{
    Texture* tex = new Texture();
    SDL_Rect rect;
    SDL_Surface* surface = IMG_Load(filePath);
    tex->texture = SDL_CreateTextureFromSurface(renderer, surface);
    tex->rect = rect;
    SDL_FreeSurface(surface);

    return tex;
}

Texture* TextureManager::LoadTextureText(int screenWidth, const char* fontPath, int fontSize, const char* text, SDL_Color color, SDL_Renderer* renderer)
{
    TTF_Init();
    Texture* tex = new Texture();
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Rect rect;
    tex->texture = SDL_CreateTextureFromSurface(renderer, surface);
    tex->rect = rect;
    tex->rect.x = screenWidth - 250;
    tex->rect.y = 150;
    tex->rect.w = surface->w;
    tex->rect.h = surface->h;

    SDL_FreeSurface(surface);
    TTF_Quit();
    return tex;
}