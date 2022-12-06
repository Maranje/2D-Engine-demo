#pragma once
#include "pause.h"

class pizzaPause :
    public pause
{
public:
    pizzaPause(class game* Game, class element* Owner, class input* ESC);
    ~pizzaPause();
private:
    void runPause() override;
    int selection;
    bool animate;
    bool run;
    class element* owner;
    class input* enter;
    class input* up;
    class input* down;
    class input* esc;
    class sprite* menuScreen;
};
