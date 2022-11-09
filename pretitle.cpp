#include "pretitle.h"
#include "element.h"
#include "sprite.h"

pretitle::pretitle(game* Game) : scene(Game) {
	sGame->resetCamera();

	//Logo = nullptr;
	//logo = nullptr;

	load();
}

void pretitle::load() {
	Logo = new element(sGame);
	logo = new sprite(Logo, 480, 270);
	logo->setTexture("assets/art/temp_logo.png");
	logo->setSource(0, 0, 480, 270);
	logo->setAnimated(
		true,
		Vector2(2400, 2430),
		5, 9,
		5000,
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(4, 8),
		1
	);
}

void pretitle::unload() {
	delete Logo;
	sceneState = inactive;
	sGame->setScene(sGame->Title);
	sGame->load();
}

void pretitle::update(float deltaTime) {
	if (!logo->getAnimated()) runUnload = true;
}