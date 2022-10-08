#pragma once
#include "component.h"

class collider :
    public component
{
public:
    collider(element* Owner, int SW, int SH);
    ~collider();
    void update(float deltaTime) override;

    //set the width and height of a collision body and its cartesian position relative to
    //the component element using its center point as the origin
    void setCollisionBody(int Width, int Height, Vector2 OffCenterPosition = Vector2(0, 0));
    //detect a collision between this object and all other collision objects in the current scene    
    bool detectCollision();

    //returns collision body rect
    SDL_Rect* getCollisionBodyRect() { return collisionRect; }

private:
    void checkCollisionWide();
    bool checkCollisionLocal();

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

