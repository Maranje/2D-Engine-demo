#pragma once
#include "component.h"

class sprite :
    public component
{
public:
    //sprite constructor, draw order set to an arbitrarily low number by default
    sprite(element* Owner, int Width, int Height, int DrawOrder = -999999999, Vector2 Offset = Vector2(0, 0));
    ~sprite() override;

    void update(float deltaTime) override;
    void draw();

    /////////////////////////////////////// getters/setters ///////////////////////////////////////
    void setDrawOrder(int DrawOrder) { drawOrder = DrawOrder; }
    void setDrawOrderByVerticalPosition(int Offset = 0);
    void setDrawOrderByHorizontalPosition(int Offset = 0);
    int getDrawOrder() const { return drawOrder; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void setTexture(const char* Texture);// { texture = textures::LoadTexture(Texture, renderer); }
    int getRuns() { return runs; }

    //sets the element to be unaffected by camera
    void setCameraNeutral(bool CameraNeutral = true) { cameraNeutral = CameraNeutral; }

    void updateDrawOrder();
    void setSource(int X, int Y, int W, int H);
    void haltAnimation() { animated = false; }
    void setAnimated(
        bool Animated,
        Vector2 SheetSize,
        int FrameCount_x,
        int FrameCount_y,
        int FPS,
        Vector2 beginAt,
        Vector2 CycleFrom,
        Vector2 CycleUntil,
        int numberOfCycles = -1
    );
    bool getAnimated() { return animated; }
    
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
    Vector2 offset;
    bool animated;
    bool cameraNeutral;
    int frameCount_x;
    int frameCount_y;
    int drawOrder;
    int width;
    int height;
    int cycles;
    int fps;
    unsigned int runs;
    float frame;
};
