#include "red_herring.h"
#include "_Polly.h"
#include "input.h"
#include "element.h"
#include "sprite.h"
#include "collider.h"
#include "interaction.h"
#include "camera.h"

red_herring::red_herring(game* Game, SDL_Renderer* Renderer, float Scale) : scene(Game) {
	renderer = Renderer;
	scale = Scale;

	polly = nullptr;
	exit = nullptr;
	Background = nullptr;
	background = nullptr;

	Floor = nullptr;
	floor = nullptr;
	boundN = nullptr;
	boundS = nullptr;
	boundE = nullptr;
	boundW = nullptr;

	Counter = nullptr;
	counter = nullptr;
	counterBody = nullptr;

	DoughStack = nullptr;
	doughStack = nullptr;
	doughStackBody = nullptr;

	FlourStation = nullptr;
	flourStation = nullptr;
	flourStationBody = nullptr;

	TrayStation = nullptr;
	trayStation = nullptr;
	trayStationBody = nullptr;

	OvenMain = nullptr;
	OvenBelt = nullptr;
	ovenMain = nullptr;
	ovenBelt = nullptr;
	ovenMainBody = nullptr;
	ovenBeltBody = nullptr;

	load();
}

void red_herring::load() {
	polly = new _Polly(sGame, renderer, scale);
	polly->getPollyCam()->cameraHaltX(true);
	exit = new input(polly, SDL_SCANCODE_RETURN);

	Background = new element(sGame);
	background = new sprite(Background, renderer, 480, 480);
	background->setTexture("assets/art/background.png");
	background->setCameraNeutral();

	for (int i = 0; i < 2; i++) {
		element* Pizza = new element(sGame);
		Pizza->setPosition(Vector2(0, (i * 300)));
		sprite* pizza = new sprite(Pizza, renderer, 1651, 300);
		pizza->setTexture("assets/art/pizza_bckgnd.png");
		pizza->setCameraNeutral();
		pizzas.emplace_back(Pizza);
	}

	Floor = new element(sGame);
	floor = new sprite(Floor, renderer, 172, 559);
	floor->setTexture("assets/art/pizza_floor.png");
	boundN = new collider(Floor);
	boundN->setCollisionBody(172, 10, Vector2(0, 279));
	boundS = new collider(Floor);
	boundS->setCollisionBody(172, 10, Vector2(0, -279));
	boundE = new collider(Floor);
	boundE->setCollisionBody(10, 559, Vector2(86, 0));
	boundW = new collider(Floor);
	boundW->setCollisionBody(10, 559, Vector2(-86, 0));

	Counter = new element(sGame);
	Counter->setPosition(Vector2(0, -180));
	counter = new sprite(Counter, renderer, 165, 85);
	counter->setDrawOrderByVerticalPosition();
	counter->setTexture("assets/art/front_counter.png");
	counterBody = new collider(Counter);
	counterBody->setCollisionBody(165, 22, Vector2(0, -32));

	DoughStack = new element(sGame);
	DoughStack->setPosition(Vector2(-60, -90));
	doughStack = new sprite(DoughStack, renderer, 49, 50);
	doughStack->setDrawOrderByVerticalPosition(25);
	doughStack->setTexture("assets/art/dough_stack.png");
	doughStackBody = new collider(DoughStack);
	doughStackBody->setCollisionBody(49, 30, Vector2(0, -11));

	FlourStation = new element(sGame);
	FlourStation->setPosition(Vector2(-62, -37));
	flourStation = new sprite(FlourStation, renderer, 44, 55);
	flourStation->setDrawOrderByVerticalPosition(25);
	flourStation->setTexture("assets/art/flour_station.png");
	flourStationBody = new collider(FlourStation);
	flourStationBody->setCollisionBody(44, 30, Vector2(0, -11));

	TrayStation = new element(sGame);
	TrayStation->setPosition(Vector2(-62, 0));
	trayStation = new sprite(TrayStation, renderer, 43, 56);
	trayStation->setDrawOrderByVerticalPosition(25);
	trayStation->setTexture("assets/art/tray_station.png");
	trayStationBody = new collider(TrayStation);
	trayStationBody->setCollisionBody(44, 30, Vector2(0, -11));

	OvenMain = new element(sGame);
	OvenBelt = new element(sGame);
	OvenMain->setPosition(Vector2(5, 75));
	OvenBelt->setPosition(Vector2(5, 68));
	ovenMain = new sprite(OvenMain, renderer, 59, 63);
	ovenMain->setDrawOrderByVerticalPosition();
	ovenMain->setTexture("assets/art/oven_mainbody.png");
	ovenMainBody = new collider(OvenMain);
	ovenMainBody->setCollisionBody(59, 30, Vector2(0, -11));
	ovenBelt = new sprite(OvenBelt, renderer, 85, 40);
	ovenBelt->setTexture("assets/art/oven_belt.png");
	ovenBelt->setSource(0, 0, 85, 40);
	ovenBelt->setDrawOrderByVerticalPosition(20);
	ovenBeltBody = new collider(OvenBelt);
	ovenBeltBody->setCollisionBody(85, 30, Vector2(0, -11));
	ovenBelt->setAnimated(
		true,
		Vector2(255, 160),
		3, 4,
		500,
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(2, 3)
	);
}

void red_herring::unload() {
	delete polly;
	delete Background;
	for (auto slice : pizzas) delete slice;
	delete Floor;
	delete Counter;
	delete DoughStack;
	delete FlourStation;
	delete TrayStation;
	delete OvenMain;
	delete OvenBelt;
	sceneState = inactive;
	sGame->setScene(sGame->Pretitle);
	sGame->load();
}

void red_herring::update(float deltaTime) {
	if (exit->getPress()) runUnload = true;

	//set cam limits
	if (polly->getPosition().y < -47 || polly->getPosition().y > 1471) {
		polly->getPollyCam()->cameraHaltY(true);
	}
	else polly->getPollyCam()->cameraHaltY(false);

	//movement for background pizza slices
	for (auto slice : pizzas) {
		Vector2 position = slice->getPosition();
		if (position.y > 450 * scale) {
			slice->setPosition(Vector2(0, 300));
		}
		else {
			slice->increaseHorizontalPosition(19);
			slice->increaseVerticalPosition(-19);
		}
	}
}