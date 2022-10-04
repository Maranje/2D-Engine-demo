#pragma once
#include "element.h"
class _Polly :
    public element
{
public:
    _Polly(game* Game, SDL_Renderer* Renderer, int SW, int SH, float Scale);

    void updateElement(float deltaTime) override;
    void unload();

private:
    class sprite* polly;
    class camera* pollyCam;

    Vector2 position;
    class input* up;
    class input* down;
    class input* left;
    class input* right;
    bool buttonPress;
    float scale;
    int fps;
};

