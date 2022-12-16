#pragma once
#include "game.h"

class scene
{
public:
	//mark the state of the scene
	enum state {
		active,
		inactive,
		paused
	};
	
	scene(game* Game);
	~scene();

	virtual void load();//load scene
	virtual void unload();//unload scene

	//run the UnloadScene process which marks the current scene as one to be unloaded
	//for the game class to remove it from the scene vector and create room for the subsequent scene
	void runUnloadScene() { runUnload = true; }

	//virtual void for a scene's update loop
	virtual void update(float deltaTime);

	/////////////////////////////////////// getters/setters ///////////////////////////////////////

	//returns unload status. useful in particular instances
	bool getUnloadStatus() { return runUnload; }
	//returns the current state of the current scene
	state getState() { return sceneState; }

protected: 
	SDL_Renderer* renderer;
	bool runUnload;
	state sceneState;
	game* sGame;

};

