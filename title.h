#pragma once
#include "scene.h"
class title :
    public scene
{
public:
    title(game* Game);

    void load() override;
    void unload() override;
    void update(float deltaTime) override;
    void start();
    void blitOrderUp();
    void blitPolly();

private:
    SDL_Renderer* renderer;
    class element* Background;
    class sprite* background;
    class element* TitleCard;
    class sprite* titleCard;
    const Uint8* keyState;
    Mix_Music* theme;
    Mix_Chunk* blit;
    Mix_Chunk* blat;

    std::vector<class element*> pizzas;

    class element* Fade;
    class sprite* fade;
    class element* OrderUp;
    class sprite* orderUp;
    class element* Polly;
    class sprite* polly;

    bool startBlit;
    bool nextBlit;
    bool lastBlit;

    class input* startInput;

    int volume;
};
