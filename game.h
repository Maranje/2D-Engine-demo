#pragma once
#include <vector>
#include <iostream>
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

class game
{
public:
	//scenes
	enum scene_type {
		Pretitle,
		Title,
		Intro,
		RedHerring,
		Test_Area
	};

	//constructor
	game();
	//destructor closes out all initialized SDL objects
	~game();

	//initialize game
	bool init();
	//main game loop
	void runLoop();
	//load scenes
	void load();

	/////////////////////////////////////// adders/removers ///////////////////////////////////////
	void addElement(class element* element);
	void removeElement(class element* element);

	/////////////////////////////////////// getters/setters ///////////////////////////////////////
	void setScene(scene_type Scene) { scene = Scene; }
	scene_type getScene() { return scene; }

private:
	//begin process for user input
	void processInput();
	//update all elements in game
	void update();
	//generate audio/video output
	void generateOutput();
	//generate delta time
	void generateDeltaTime();

	//SDL window pointer to produce game window
	SDL_Window* window;
	//SDL renderer pointer for rendering all imamges
	SDL_Renderer* renderer;

	//bool remains true while game is running
	bool run;

	//current scene
	scene_type scene;

	//SDL event for user input
	SDL_Event* event;

	const Uint8* keyState;

	//values for storing screen proportions
	int screenWidth;
	int screenHeight;
	int scale;

	//float for storing delta time
	float deltaTime;
	int ticks;

	//true if currently updating active elements
	bool updatingElements;
	//stores all active elements in current scene
	std::vector<class element*> elements;
	//temporarily stores elements if added while updating all elements
	std::vector<class element*> elementCue;
};


/* vector2 class for 2D in-game positions*/

class Vector2{
public:
	int x;
	int y;

	//constructor sets initial values for x and y
	Vector2() : x(0), y(0){}

	//explicitly set x and y when creating a Vector2 object
	explicit Vector2(int X, int Y) : x(X), y(Y){}

	//set values for x and y
	void set(int X, int Y) {
		x = X;
		y = Y;
	}
};