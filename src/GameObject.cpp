#include "GameObject.hpp"

GameObject::GameObject(const char* filePath, Size* s, SDL_Renderer* rend)
{
    tex = TextureManager::LoadTexture(filePath, renderer);
    renderer = rend;
    position = new Position(0,0);
    size = s;
    // tex->destRect->x = position->x;
    // tex->destRect->y = position->y;
}

GameObject::~GameObject()
{

}

void GameObject::render()
{
    SDL_RenderCopy(renderer, tex->texture, tex->srcRect, tex->destRect);
}

void GameObject::update(Position* pos)
{
    position = pos;

    tex->srcRect->h = size->height;
    tex->srcRect->w = size->width;
    tex->srcRect->x = 0;
    tex->srcRect->y = 0;

    tex->destRect->x = position->x;
    tex->destRect->y = position->x;
    tex->destRect->w = size->width;
    tex->destRect->h = size->height;
}

void GameObject::clean()
{
    SDL_DestroyTexture(tex->texture);
}