#include "test_area.h"
#include "_Polly.h"
#include "input.h"
#include "element.h"
#include "sprite.h"
#include "collider.h"
#include "interaction.h"

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
	testAct = nullptr;

	Test2 = nullptr;
	test2 = nullptr;
	testBody2 = nullptr;

	load();
}

void test_area::load() {
	polly = new _Polly(sGame, renderer, scale);
	Background = new element(sGame);
	background = new sprite(Background, renderer, 480, 480); //set draw order arbitrarily low for background
	background->setTexture("assets/art/background.png");
	exit = new input(polly, SDL_SCANCODE_RETURN);

	Test = new element(sGame);
	Test->setPosition(Vector2(50, 50));
	test = new sprite(Test, renderer, 49, 50); 
	test->setDrawOrderByVerticalPosition(25);//set draw order according to position onscreen and tweaked to optimize
	test->setTexture("assets/art/dough_stack.png");
	testBody = new collider(Test);
	testBody->setCollisionBody(49, 36, Vector2(0, -12));
	testAct = new interaction(Test);
	testAct->setInteractionArea(60, 60);

	Test2 = new element(sGame);
	Test2->setPosition(Vector2(50, 125));
	test2 = new sprite(Test2, renderer, 49, 50);
	test2->setDrawOrderByVerticalPosition(25);
	test2->setTexture("assets/art/dough_stack.png");
	testBody2 = new collider(Test2);
	testBody2->setCollisionBody(49, 36, Vector2(0, -12));
}

void test_area::update(float deltaTime) {
	if (exit->getPress()) runUnload = true;
}

void test_area::unload() {
	delete polly;
	delete Background;
	delete Test;
	delete Test2;
	sceneState = inactive;
	sGame->setScene(sGame->Pretitle);
	sGame->load();
}

