#include "scene.h"

scene::scene(game* Game) {
	sGame = Game;
	sceneState = active;
	runUnload = false;
	sGame->addScene(this);
}

scene::~scene() {
	sGame->removeScene(this);
}

void scene::load(){}

void scene::unload(){}

void scene::update(){}