#pragma once
#include "component.h"
class input :
    public component
{
public:
    input(element* Owner, int ScanCode);
    
    //returns true if key is pressed
    bool getPress();
    //returns true only once if key is lifted
    bool getLift();

private:
    const Uint8* keyState;
    int scanCode;
    bool wasPressed;
};
