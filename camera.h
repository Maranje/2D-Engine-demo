#pragma once
#include "component.h"

class camera : public component
{
public:
	camera(element* Owner);

	//update camera position based on owner element position
	void update(float deltaTime) override;

private:
	element* owner;
	int x; //x-position
	int y; //y-position
};

