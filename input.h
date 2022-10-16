#pragma once
#include "component.h"
class input :
    public component
{
public:
    input(element* Owner, int ScanCode);
    
    //returns true only once if key is pressed
    bool getPress();
    //returns true if key is pressed
    bool getActivePress();
    //returns true only once if key is lifted
    bool getLift();
    //returns if key is being currently pressed
    void resetKey() { wasPressed = false; }

private:
    const Uint8* keyState;
    int scanCode;
    bool wasPressed;
};
