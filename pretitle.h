#pragma once
#include "scene.h"
class pretitle :
    public scene
{
public:
    pretitle(game* Game);

    void load() override;
    void unload() override;
    void update(float deltaTime) override;

private:
    class element* Logo;
    class sprite* logo;

};

