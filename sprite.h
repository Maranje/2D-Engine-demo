#pragma once
#include "component.h"

class sprite :
    public component
{
public:
    sprite(element* Owner, SDL_Renderer* Renderer, int Width, int Height, int DrawOrder = 100);
    ~sprite() override;

    void update(float deltaTime) override;
    void draw();

    /////////////////////////////////////// getters/setters ///////////////////////////////////////

    int getDrawOrder() const { return drawOrder; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void setTexture(const char* Texture);// { texture = textures::LoadTexture(Texture, renderer); }

    void setSource(int X, int Y, int W, int H);
    void setAnimated(
        bool Animated,
        Vector2 SheetSize,
        int FrameCount_x,
        int FrameCount_y,
        int FPS,
        Vector2 CycleFrom,
        Vector2 CycleUntil,
        int numberOfCycles = -1
    );
    
    void destroyTexture();

private:
    element* owner;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect* drawRect;
    SDL_Rect* source;
    Vector2 sheetSize;
    Vector2 cycleFrom;
    Vector2 cycleUntil;
    bool animated;
    int frameCount_x;
    int frameCount_y;
    int drawOrder;
    int width;
    int height;
    int cycles;
    int frame;
    int fps;
    int runs;
};
