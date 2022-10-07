#pragma once
#include "component.h"

class collider :
    public component
{
public:
    collider(element* Owner, int SW, int SH);
    ~collider();
    void update(float deltaTime) override;
    void checkCollisionWide();
    bool checkCollisionLocal();

    void setCollisionBody(int Width, int Height, Vector2 OffCenterPosition = Vector2(0, 0));
    SDL_Rect* getCollisionBodyRect() { return collisionRect; }
    
    bool detectCollision();

private:
    element* owner;
    SDL_Rect* localRect;
    SDL_Rect* collisionRect;
    Vector2 center;
    Vector2 offCenterPosition;
    bool scanWide;
    
    int screenWidth;
    int screenHeight;
    std::vector<collider*> localColliders;
};

