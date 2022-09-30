#pragma once
#include "scene.h"
class title :
    public scene
{
public:
    title(game* Game, SDL_Renderer* Renderer, int SW, int SH, int scale);

    void load() override;
    void unload() override;
    void update() override;

private:
    SDL_Renderer* renderer;
    int screenWidth, screenHeight, scale;
    class element* Background;
    class sprite* background;
    class element* TitleCard;
    class sprite* titleCard;
    const Uint8* keyState;
};

