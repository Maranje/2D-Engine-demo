#include "pretitle.h"
#include "element.h"
#include "sprite.h"

pretitle::pretitle(game* Game, SDL_Renderer* Renderer, float Scale) : scene(Game) {
	renderer = Renderer;
	scale = Scale;

	sGame->resetCamera();

	Logo = nullptr;
	logo = nullptr;

	load();
}

void pretitle::load() {
	Logo = new element(sGame);
	logo = new sprite(Logo, renderer, static_cast<int>(480.0f * scale), static_cast<int>(270.0f * scale));
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