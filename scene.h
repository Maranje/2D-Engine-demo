#pragma once
#include "game.h"

class scene
{
public:
	enum state {
		active,
		inactive,
		paused
	};

	scene(game* Game);
	~scene();

	virtual void load();
	virtual void unload();

	virtual void update(float deltaTime);

	/////////////////////////////////////// getters/setters ///////////////////////////////////////

	bool getUnloadStatus() { return runUnload; }
	state getState() { return sceneState; }

protected: 
	bool runUnload;
	state sceneState;
	game* sGame;

};

