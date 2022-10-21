#pragma once
#include "component.h"

class camera : public component
{
public:
	camera(element* Owner);

	//update camera position based on owner element position
	void update(float deltaTime) override;
	//determines whether the camera movement is halted or not in the horizontal direction
	void cameraHaltX(bool Halt) { haltX = Halt; }
	//determines whether the camera movement is halted or not in the vertical direction
	void cameraHaltY(bool Halt) { haltY = Halt; }

private:
	element* owner;
	int x; //x-position
	int y; //y-position
	bool haltX;
	bool haltY;
};

