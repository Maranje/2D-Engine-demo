#include "test_area.h"
#include "_Polly.h"
#include "input.h"
#include "element.h"
#include "sprite.h"
#include "collider.h"

test_area::test_area(game* Game, SDL_Renderer* Renderer, float Scale) : scene(Game) {
	renderer = Renderer;
	scale = Scale;

	polly = nullptr;
	Background = nullptr;
	background = nullptr;
	exit = nullptr;

	Test = nullptr;
	test = nullptr;
	testBody = nullptr;

	load();
}

void test_area::load() {
	polly = new _Polly(sGame, renderer, scale);
	Background = new element(sGame);
	background = new sprite(Background, renderer, static_cast<int>(480.0f * scale), static_cast<int>(480.0f * scale), 0);
	background->setTexture("assets/art/background.png");
	exit = new input(polly, SDL_SCANCODE_RETURN);

	Test = new element(sGame);
	Test->setPosition(Vector2(100, 200));
	test = new sprite(Test, renderer, static_cast<int>(49.0f * scale), static_cast<int>(50.0f * scale), 1);
	test->setTexture("assets/art/dough_stack.png");
	testBody = new collider(Test);
	testBody->setCollisionBody(static_cast<int>(49.0f * scale), static_cast<int>(50.0f * scale));
}

void test_area::update(float deltaTime) {
	if (exit->getPress()) runUnload = true;
}

void test_area::unload() {
	delete polly;
	delete Background;
	delete Test;
	sceneState = inactive;
	sGame->setScene(sGame->Pretitle);
	sGame->load();
}

