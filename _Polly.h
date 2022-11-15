#pragma once
#include "element.h"

class _Polly :
    public element
{
public:
    _Polly(game* Game);
    
    void updateElement(float deltaTime) override;
    void unload();
    void processInput();

    void setPollySpeed(int Speed) { pollySpeed = Speed; }
    int getPollySpeed() { return pollySpeed; }

    //assign walking animation
    void setAnimation();

    //get the camera
    class camera* getPollyCam() { return pollyCam; }

    enum Direction {
        Up,
        Down,
        Left,
        Right
    };

private:
    class sprite* polly;
    class sprite* shadow;
    class camera* pollyCam;
    class collider* pollyCollider;
    class interaction* pollyAction;

    Vector2 position;
    Direction direction;
    std::vector<Direction> directions;
    class input* up;
    class input* down;
    class input* left;
    class input* right;
    class input* action;
    int currentPressed;
    int pollySpeed;
    bool move;

};

