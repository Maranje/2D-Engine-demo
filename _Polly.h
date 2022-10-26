#pragma once
#include "element.h"

class _Polly :
    public element
{
public:
    _Polly(game* Game, SDL_Renderer* Renderer);
    
    void updateElement(float deltaTime) override;
    void unload();
    void processInput();

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
    bool move;

};

