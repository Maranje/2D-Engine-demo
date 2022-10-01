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
	//clear vectors
	void clearVectors();

	/////////////////////////////////////// adders/removers ///////////////////////////////////////

	//adds an element to the elements vector
	void addElement(class element* element);
	//removes passed element from elements
	void removeElement(class element* element);
	//adds a sprite to the sprites vector
	void addSprite(class sprite* sprite);
	//removes passed sprite from sprites
	void removeSprite(class sprite* sprite);
	//adds active scene to scenes
	void addScene(class scene* Scene);
	//removes inactive scenes from scene
	void removeScene(class scene* Scene);
	//add a collision detection object
	void addCollider(class collider* Collider);
	//remove collision detection object
	void removeCollider(class collider* Collider);

	/////////////////////////////////////// getters/setters ///////////////////////////////////////

	//get current active scene
	scene_type getScene() { return sceneTag; }
	//set a new value for active scene
	void setScene(scene_type Scene) { sceneTag = Scene; }
	//gets the camera rect
	SDL_Rect* getCamera() { return Camera; }
	//sets camera x and y positions
	void setCamera(int X, int Y) {
		Camera->x = X;
		Camera->y = Y;
	}

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
	//SDL rect used as camera
	SDL_Rect* Camera;

	//bool remains true while game is running
	bool run;

	//current scene tag
	scene_type sceneTag;

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
	//temporarily stores elements if removed while updating all elements
	std::vector<class element*> elementBin;
	//stores all active elements sprites
	std::vector<class sprite*> sprites;
	//stores current active scene
	std::vector<class scene*> scenes;
	//stores all collision detection objects that are in the current scene
	std::vector<class collider*> colliders;

	//game scenes
	class pretitle* pretitleScene;
	class title* titleScene;


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