#pragma once
#include "component.h"

class sprite :
    public component
{
public:
    //sprite constructor, draw order set to an arbitrarily low number by default
    sprite(element* Owner, int Width, int Height, Vector2 Offset = Vector2(0, 0), int DrawOrder = -999999999);
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
    void setTexture(const char* Texture);
    void updateTexture(const char* Texture, int layer);
    int getRuns() { return runs; }
    void setOffset(Vector2 Offset) { offset = Offset; }
    void lend(element* Receiver) { owner = Receiver; }

    //sets the element to be unaffected by camera
    void setCameraNeutral(bool CameraNeutral = true) { cameraNeutral = CameraNeutral; }

    void updateDrawOrder();
    void setSource(int X, int Y, int W, int H);
    void setCentered(bool Centered) { centered = Centered; }
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

    bool getTextSet(int Tex);
    
    void destroyTexture();

    void setGlow(bool Glowing, int Border = 0);

private:
    void initGlowing(int Border);
    element* owner;
    SDL_Renderer* renderer;
    SDL_Texture* texture0;
    SDL_Texture* texture1;
    SDL_Texture* texture2;
    SDL_Texture* texture3;
    SDL_Texture* texture4;
    SDL_Texture* texture5;
    SDL_Texture* texture6;
    SDL_Texture* texture7;
    SDL_Texture* texture8;
    SDL_Rect* drawRect;
    SDL_Rect* source;
    SDL_Rect* glow;
    Vector2 sheetSize;
    Vector2 cycleFrom;
    Vector2 cycleUntil;
    Vector2 offset;
    bool centered;
    bool animated;
    bool cameraNeutral;
    bool glowing;
    bool tex1;
    bool tex2;
    bool tex3;
    bool tex4;
    bool tex5;
    bool tex6;
    bool tex7;
    bool tex8;
    int frameCount_x;
    int frameCount_y;
    int drawOrder;
    int width;
    int height;
    int cycles;
    int fps;
    int glowAlpha;
    int glowFactor;
    unsigned int runs;
    float frame;
};
