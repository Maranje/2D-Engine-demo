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

    /// <summary>adds up to 7 layerst to an existing sprite texture</summary>
    /// <param name="Texture: filepath of the image to be added"></param>
    /// <param name="layer: int ranging from 1-8 for indicating layer level. 1 = bottom-most, 8 = top"></param>
    void updateTexture(const char* Texture, int layer);
    int getRuns() { return runs; }
    void setOffset(Vector2 Offset) { offset = Offset; }
    void lend(element* Receiver) { owner = Receiver; }

    ///<summary>sets the element to be unaffected by camera</summary>
    ///<param name="CameraNeutral: bool to toggle camera neutrality"></param>
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

    /// <summary>applies a glowing effect to a sprite</summary>
    /// <param name="Glowing: bool to set glow effect on or off"></param>
    /// <param name="Border: int to expand the size of the glow, default value is 0"></param>
    void setGlow(bool Glowing, int Border = 0);

    /// <summary>
    /// <para>initiallizes the aux rectangle sprite for a sprite object </para>
    /// <para>size and position parameters are minimized values for fine tuning</para>
    /// </summary>
    /// <param name="x: shift rect horizontal position"></param>
    /// <param name="y: shift rect vertical position"></param>
    /// <param name="h: rect height"></param>
    /// <param name="w: rect width"></param>
    /// <param name="r: red color value for rect fill"></param>
    /// <param name="g: green color value for rect fill"></param>
    /// <param name="b: blue color value for rect fill"></param>
    /// <param name="a: alpha value for rect colors"></param>
    void initAuxRect(int x, int y, int h, int w, int r, int g, int b, int a);
    void destroyAuxRect();
    void updateAuxRectWidth(int w);
    void updateAuxRectHeight(int h);
    void updateAuxRectXPos(int x);
    void updateAuxRectYPos(int y);

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
    SDL_Rect* auxRect;
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
    int auxRGBA[4];
    int auxPosShift[2];
    unsigned int runs;
    float frame;
};
