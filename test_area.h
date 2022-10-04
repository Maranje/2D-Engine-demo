#pragma once
#include "scene.h"
class test_area :
    public scene
{
public:
    test_area(game* Game, SDL_Renderer* Renderer, int SW, int SH, float Scale);

    void load() override;
    void unload() override;
    void update(float deltaTime) override;

private:
    SDL_Renderer* renderer;
    int screenWidth, screenHeight;
    float scale;

    class _Polly* polly;
    class element* Background;
    class sprite* background;
    class input* exit;


};

