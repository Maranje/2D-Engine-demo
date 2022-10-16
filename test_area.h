#pragma once
#include "scene.h"
class test_area :
    public scene
{
public:
    test_area(game* Game, SDL_Renderer* Renderer, float Scale);

    void load() override;
    void unload() override;
    void update(float deltaTime) override;

private:
    SDL_Renderer* renderer;
    float scale;

    class _Polly* polly;
    class element* Background;
    class sprite* background;
    class input* exit;

    class element* Test;
    class sprite* test;
    class collider* testBody;
    class interaction* testAct;

    class element* Test2;
    class sprite* test2;
    class collider* testBody2;
};

