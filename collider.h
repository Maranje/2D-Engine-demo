#pragma once
#include "component.h"

class collider :
    public component
{
public:
    collider(element* Owner);
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
    //checks all collision objects in scene to store them in localColliders vector
    //if they are located within the bounds of the screen. if the main collision detecting
    //object wanders near the preset bounds of the screen, the function will clear the
    //localCollisions vector, scan for collision objects again, and set new screen bounds
    void checkCollisionWide();

    //checks every collision object in localColliders. returns true if a collision is detected.
    //note: this function does not identify which objects collided, it seemed like a waste to include
    //that information when the interact component already does that. colliders only flag collisions
    //between collider objects for the designer to implement on a case by case basis
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

