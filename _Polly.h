#pragma once
#include "element.h"

class _Polly :
    public element
{
public:
    _Polly(game* Game, SDL_Renderer* Renderer, float Scale);
    
    void updateElement(float deltaTime) override;
    void unload();
    void processInput();

    //assign walking animation
    void setAnimation();

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

    Vector2 position;
    Direction direction;
    std::vector<Direction> directions;
    class input* up;
    class input* down;
    class input* left;
    class input* right;
    int currentPressed;
    bool move;

    float scale;
};

