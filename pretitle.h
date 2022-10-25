#pragma once
#include "scene.h"
class pretitle :
    public scene
{
public:
    pretitle(game* Game, SDL_Renderer* Renderer);

    void load() override;
    void unload() override;
    void update(float deltaTime) override;

private:
    SDL_Renderer* renderer;
    class element* Logo;
    class sprite* logo;

};

