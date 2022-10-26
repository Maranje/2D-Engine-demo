#pragma once
#include "scene.h"
class red_herring :
    public scene
{
public:
    red_herring(game* Game, SDL_Renderer* Renderer);

    void load() override;
    void unload() override;
    void update(float deltaTime) override;

private:
    SDL_Renderer* renderer;

    class _Polly* polly;
    class input* exit;

    class element* Background;
    class sprite* background;

    std::vector<class element*> pizzas;

    class element* Floor;
    class sprite* floor;
    class collider* boundN;
    class collider* boundS;
    class collider* boundE;
    class collider* boundW;

    class element* Counter;
    class sprite* counter;
    class collider* counterBody;

    class element* DoughStack;
    class sprite* doughStack;
    class collider* doughStackBody;

    class element* FlourStation;
    class sprite* flourStation;
    class collider* flourStationBody;

    class element* TrayStation;
    class sprite* trayStation;
    class collider* trayStationBody;

    class element* OvenMain;
    class element* OvenBelt;
    class sprite* ovenMain;
    class sprite* ovenBelt;
    class collider* ovenMainBody;
    class collider* ovenBeltBody;

    class element* Wall;
    class sprite* wall;
    class collider* wallBody;

    class element* Poster;
    class sprite* poster;

    class element* Mat;
    class sprite* mat;

    class element* BackroomShade;
    class sprite* backroomShade;

    class element* Roger;
    class sprite* roger;
    class collider* rogerBody;
    class interaction* rogerInteraction;
    bool rogerSleep;

};

