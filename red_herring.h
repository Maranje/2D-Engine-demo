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
        boxStage,
        ready
    };
private:
    class pizzaPause* pause;

    class _Polly* polly;
    class sprite* pizza;
    class sprite* pizzaBox;
    class sprite* steam;
    bool carryShift;
    bool pizzaReady;
    bool paused;
    int boxSprite;
    int pizzaOnOven;
    int increment;
    int readyBoxes;
    stage pizzaStage;

    class input* e;
    class input* p;

    class element* Background;
    class sprite* background;

    std::vector<class element*> pizzas;
    std::vector<class element*> allBoxes;

    class element* Boxes;
    class sprite* boxes;
    class sprite* boxSteam;

    class element* Floor;
    class sprite* floor;
    class collider* boundN;
    class collider* boundS;
    class collider* boundE;
    class collider* boundW;

    class element* Counter;
    class sprite* counter;
    class collider* counterBody;
    class interaction* counterBoxing;

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

    class element* OrderUp;
    class sprite* orderUp;

    class element* TimerBar;
    class sprite* timerBar;

    Mix_Music* theme;
    Mix_Chunk* flup;
    Mix_Chunk* dump;
    Mix_Chunk* pop;
    Mix_Chunk* pop2;
    Mix_Chunk* boxFold1;
    Mix_Chunk* boxFold2;
    Mix_Chunk* boxFold3;
    Mix_Chunk* orderKaching;
};