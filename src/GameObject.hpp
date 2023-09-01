#ifndef GameObject_hpp
#define GameObject_hpp

#include "Size.hpp"
#include "Position.hpp"
#include "TextureManager.hpp"

class GameObject 
{
public:
    GameObject(const char* filePath, Size* s, SDL_Renderer* rend);
    ~GameObject();

    void render();
    void update(Position* pos);
    void clean();

    Size* size = nullptr;
    Position* position = nullptr;
    Texture* tex = nullptr;
    SDL_Renderer* renderer = nullptr;
};

#endif