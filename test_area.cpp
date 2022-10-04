#include "test_area.h"
#include "_Polly.h"
#include "input.h"
#include "element.h"
#include "sprite.h"

test_area::test_area(game* Game, SDL_Renderer* Renderer, int SW, int SH, float Scale) : scene(Game) {
	renderer = Renderer;
	screenWidth = SW;
	screenHeight = SH;
	scale = Scale;

	polly = nullptr;
	Background = nullptr;
	background = nullptr;
	exit = nullptr;

	load();
}

void test_area::load() {
	polly = new _Polly(sGame, renderer, screenWidth, screenHeight, scale);
	Background = new element(sGame);
	Background->setPosition(Vector2((screenWidth / 2), (screenHeight / 2)));
	background = new sprite(Background, renderer, static_cast<int>(480.0f * scale), static_cast<int>(480.0f * scale), 0);
	background->setTexture("assets/art/background.png");
	exit = new input(polly, SDL_SCANCODE_RETURN);
}

void test_area::update(float deltaTime) {
	if (exit->getPress()) runUnload = true;
}

void test_area::unload() {
	delete polly;
	delete Background;
	sceneState = inactive;
	sGame->setScene(sGame->Pretitle);
	sGame->load();
}

