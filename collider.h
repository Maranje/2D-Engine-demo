#pragma once
#include "component.h"

class collider :
    public component
{
public:
    collider(element* Owner, std::string elementName);
    ~collider();

    void checkCollisionWide();
    void checkCollisionLocal();

    void setCollisionBody(int Width, int Height);
    void setCollisionBodyLocation(Vector2 Center_Position);
    SDL_Rect* getCollisionBodyRect() { return collisionRect; }
    
    bool detectCollision();

private:
    element* owner;
    SDL_Rect* localRect;
    SDL_Rect* collisionRect;
    Vector2 center;
    
    bool collision;
    int scale;
    std::string tag;
    std::vector<collider*> localColliders;
};

