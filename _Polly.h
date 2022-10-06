#pragma once
#include "element.h"

class _Polly :
    public element
{
public:
    _Polly(game* Game, SDL_Renderer* Renderer, int SW, int SH, float Scale);
    
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

    Vector2 position;
    std::vector<Direction> directions;
    class input* up;
    class input* down;
    class input* left;
    class input* right;
    int currentPressed;
    bool move;

    float scale;
};

