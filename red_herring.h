#pragma once
#include "scene.h"
class red_herring :
    public scene
{
public:
    red_herring(game* Game);

    void load() override;
    void unload() override;
    void update(float deltaTime) override;

    enum stage {
        free,
        doughStage,
        prepStage,
        cookStage,
        boxStage
    };
private:
    SDL_Renderer* renderer;

    class _Polly* polly;
    class sprite* pizza;
    class sprite* steam;
    int pizzaOnOven;
    int increment;
    stage pizzaStage;

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
    class interaction* dough;

    class element* FlourStation;
    class sprite* flourStation;
    int flattens;
    class collider* flourStationBody;
    class interaction* flatten;

    class element* TrayStation;
    class sprite* trayStation;
    class collider* trayStationBody;

    class element* OvenMain;
    class element* OvenBelt;
    class sprite* ovenMain;
    class sprite* ovenBelt;
    class collider* ovenMainBody;
    class collider* ovenBeltBody;
    class interaction* ovenSet;
    class interaction* ovenGet;

    class element* Wall;
    class sprite* wall;
    class collider* wallBody;

    class element* Mat;
    class sprite* mat;

    class element* Roger;
    class sprite* roger;
    class collider* rogerBody;
    class interaction* rogerInteraction;
    bool rogerSleep;

    class element* Ingredients;
    class sprite* ingredients;
    class collider* ingredientsBody;
    class interaction* ingredientsAct;
    class sprite* ingredient;
    bool label;

    class element* Mop;
    class sprite* mop;
    class collider* mopBody;

    class element* Box;
    class sprite* box;
    class collider* boxBody;

    class element* Wall2;
    class sprite* wall2;
    class collider* wall2Body;

    class element* CRT;
    class sprite* crt;

    class element* Door;
    class sprite* door;
    bool pollySouth;

    class element* Can;
    class sprite* can;
    class collider* canBody;
    class interaction* trash;

    class element* SealedStack;
    class sprite* sealedStack;
    class collider* sealedStackBody;

    Mix_Music* theme;
    Mix_Chunk* flup;
    Mix_Chunk* dump;

};