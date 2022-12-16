#include "scene.h"

//scene constructor
scene::scene(game* Game) {
	sGame = Game;
	sceneState = active;
	renderer = sGame->getRenderer();
	runUnload = false;
	sGame->addScene(this); //add this scene to the scene vector in game class
}

scene::~scene() {
	sGame->removeScene(this); //remove scene from scene vector in game class
}

//virtual functions for used for objects inheriting from scene class
void scene::load(){}

void scene::unload(){}

void scene::update(float deltaTime) {}