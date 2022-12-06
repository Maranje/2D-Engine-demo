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
	void runUnloadScene() { runUnload = true; }
	virtual void update(float deltaTime);

	/////////////////////////////////////// getters/setters ///////////////////////////////////////

	bool getUnloadStatus() { return runUnload; }
	state getState() { return sceneState; }

protected: 
	SDL_Renderer* renderer;
	bool runUnload;
	state sceneState;
	game* sGame;

};

