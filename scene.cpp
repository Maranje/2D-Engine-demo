#include "scene.h"

scene::scene(game* Game) {
	sGame = Game;
	sceneState = active;
	renderer = sGame->getRenderer();
	runUnload = false;
	sGame->addScene(this);
}

scene::~scene() {
	sGame->removeScene(this);
}

void scene::load(){}

void scene::unload(){}

void scene::update(float deltaTime) {}