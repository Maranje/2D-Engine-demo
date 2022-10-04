#pragma once
#include "scene.h"
class pretitle :
    public scene
{
public:
    pretitle(game* Game, SDL_Renderer* Renderer, int SW, int SH, float Scale);

    void load() override;
    void unload() override;
    void update(float deltaTime) override;

private:
    SDL_Renderer* renderer;
    int screenWidth, screenHeight;
    float scale;
    class element* Logo;
    class sprite* logo;

};

