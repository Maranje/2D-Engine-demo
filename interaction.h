#pragma once
#include "component.h"
class interaction :
    public component
{
public:
    interaction(element* Owner);
    ~interaction();
    void update(float deltaTime) override;

    void setInteractionArea(int Width, int Height, Vector2 OffCenterPosition = Vector2(0, 0));
    bool detectInteraction();

    SDL_Rect* getInteractionRect() { return interactionRect; }

private:
    void checkInteractionWide();
    bool checkInteractionLocal();

    element* owner;
    SDL_Rect* localRect;
    SDL_Rect* interactionRect;
    Vector2 center;
    Vector2 offCenterPosition;
    bool scanWide;

    int screenWidth;
    int screenHeight;
    std::vector<interaction*> localInteractions;
};

