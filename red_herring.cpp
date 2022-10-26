#include "red_herring.h"
#include "_Polly.h"
#include "input.h"
#include "element.h"
#include "sprite.h"
#include "collider.h"
#include "interaction.h"
#include "camera.h"

red_herring::red_herring(game* Game, SDL_Renderer* Renderer) : scene(Game) {
	renderer = Renderer;

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

	//////////////////////////////game objects/////////////////////////////////
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

	Roger = nullptr;
	roger = nullptr;
	rogerBody = nullptr;
	rogerInteraction = nullptr;
	rogerSleep = false;

	Wall = nullptr;
	wall = nullptr;
	wallBody = nullptr;

	Poster = nullptr;
	poster = nullptr;

	Mat = nullptr;
	mat = nullptr;

	BackroomShade = nullptr;
	backroomShade = nullptr;

	load();
}

void red_herring::load() {
	Mix_OpenAudio(22050, AUDIO_S16SYS, 4, 4096);

	polly = new _Polly(sGame, renderer);
	polly->getPollyCam()->cameraHaltX(true);
	exit = new input(polly, SDL_SCANCODE_RETURN);

	Background = new element(sGame);
	background = new sprite(Background, renderer, 700, 480);
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
	floor = new sprite(Floor, renderer, 190, 577);
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
	counter->updateDrawOrder();
	counter->setTexture("assets/art/front_counter.png");
	counterBody = new collider(Counter);
	counterBody->setCollisionBody(165, 22, Vector2(0, -32));

	DoughStack = new element(sGame);
	DoughStack->setPosition(Vector2(-60, -90));
	doughStack = new sprite(DoughStack, renderer, 49, 50);
	doughStack->setDrawOrderByVerticalPosition(25);
	doughStack->updateDrawOrder();
	doughStack->setTexture("assets/art/dough_stack.png");
	doughStackBody = new collider(DoughStack);
	doughStackBody->setCollisionBody(49, 30, Vector2(0, -11));

	TrayStation = new element(sGame);
	TrayStation->setPosition(Vector2(-62, 0));
	trayStation = new sprite(TrayStation, renderer, 43, 56);
	trayStation->setDrawOrderByVerticalPosition(25);
	trayStation->updateDrawOrder();
	trayStation->setTexture("assets/art/tray_station.png");
	trayStationBody = new collider(TrayStation);
	trayStationBody->setCollisionBody(44, 30, Vector2(0, -11));

	FlourStation = new element(sGame);
	FlourStation->setPosition(Vector2(-62, -37));
	flourStation = new sprite(FlourStation, renderer, 44, 55);
	flourStation->setDrawOrderByVerticalPosition(25);
	flourStation->updateDrawOrder();
	flourStation->setTexture("assets/art/flour_station.png");
	flourStationBody = new collider(FlourStation);
	flourStationBody->setCollisionBody(44, 30, Vector2(0, -11));

	OvenMain = new element(sGame);
	OvenBelt = new element(sGame);
	OvenMain->setPosition(Vector2(10, 75));
	OvenBelt->setPosition(Vector2(10, 68));
	ovenMain = new sprite(OvenMain, renderer, 59, 63);
	ovenMain->setDrawOrderByVerticalPosition();
	ovenMain->updateDrawOrder();
	ovenMain->setTexture("assets/art/oven_mainbody.png");
	ovenMainBody = new collider(OvenMain);
	ovenMainBody->setCollisionBody(59, 30, Vector2(0, -11));
	ovenBelt = new sprite(OvenBelt, renderer, 85, 40);
	ovenBelt->setTexture("assets/art/oven_belt.png");
	ovenBelt->setSource(0, 0, 85, 40);
	ovenBelt->setDrawOrderByVerticalPosition(20);
	ovenBelt->updateDrawOrder();
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


	Roger = new element(sGame);
	Roger->setPosition(Vector2(60, -166));
	roger = new sprite(Roger, renderer, 22, 35);
	roger->setTexture("assets/art/Roger_bored.png");
	roger->setSource(0, 0, 22, 35);
	roger->setDrawOrderByVerticalPosition(-50);
	roger->updateDrawOrder();
	roger->setAnimated(
		true,
		Vector2(220, 245),
		10, 7,
		200,
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(9, 6)
	);
	rogerBody = new collider(Roger);
	rogerBody->setCollisionBody(30, 15, Vector2(0, -20));
	rogerInteraction = new interaction(Roger);
	rogerInteraction->setInteractionArea(40, 60);

	Wall = new element(sGame);
	Wall->setPosition(Vector2(0, 115));
	wall = new sprite(Wall, renderer, 170, 73);
	wall->setTexture("assets/art/Back_wall.png");
	wall->setDrawOrderByVerticalPosition(-10);
	wall->updateDrawOrder();
	wallBody = new collider(Wall);
	wallBody->setCollisionBody(125, 10, Vector2(20, -35));
	wallBody = new collider(Wall);
	wallBody->setCollisionBody(13, 10, Vector2(-75, -35));

	Poster = new element(sGame);
	Poster->setPosition(Vector2(60, 117));
	poster = new sprite(Poster, renderer, 20, 29);
	poster->setDrawOrderByVerticalPosition(-20);
	poster->updateDrawOrder();
	poster->setTexture("assets/art/poster.png");

	BackroomShade = new element(sGame);
	BackroomShade->setPosition(Vector2(0, 215));
	backroomShade = new sprite(BackroomShade, renderer, 171, 128);
	backroomShade->setTexture("assets/art/Backroom_shade.png");

	/*
	* i don't like how this looks 
	Mat = new element(sGame);
	Mat->setPosition(Vector2(0, -30));
	mat = new sprite(Mat, renderer, 38, 97);
	mat->setTexture("assets/art/mat.png");
	*/
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
	delete Roger;
	delete Wall;
	delete Poster;
	delete BackroomShade;

	Mix_CloseAudio();
	sceneState = inactive;
	sGame->setScene(sGame->Pretitle);
	sGame->load();
}

void red_herring::update(float deltaTime) {
	if (exit->getPress()) runUnload = true; //unload the scene

	//set cam limits
	if (polly->getPosition().y < -(10 * sGame->getScale()) || polly->getPosition().y > (263 * sGame->getScale())) {
		polly->getPollyCam()->cameraHaltY(true);
	}
	else polly->getPollyCam()->cameraHaltY(false);

	//movement for background pizza slices
	for (auto slice : pizzas) {
		Vector2 position = slice->getPosition();
		if (position.y > 450 * sGame->getScale()) {
			slice->setPosition(Vector2(0, 300));
		}
		else {
			slice->increaseHorizontalPosition(19);
			slice->increaseVerticalPosition(-19);
		}
	}
	
	//roger falls asleep
	if (roger->getRuns() == 2 && rogerSleep == false && !rogerInteraction->getObjectFlag()) {
		roger->setTexture("assets/art/Roger_sleeping.png");
		roger->setSource(0, 0, 22, 35);
		roger->setAnimated(
			true,
			Vector2(154, 140),
			7, 4,
			200,
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(6, 3)
		);
		rogerSleep = true;
	}
	//roger gets startled awake	
	if (rogerInteraction->getObjectFlag() && rogerSleep == true) {
		Roger->setPosition(Vector2(60, -166));
		roger->setTexture("assets/art/Roger_startled.png");
		roger->setSource(0, 0, 22, 35);
		roger->setAnimated(
			true,
			Vector2(88, 70),
			4, 2,
			300,
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(3, 1),
			1
			);
		rogerSleep = false;
		rogerInteraction->setObjectFlag(false);
	}
	//normal bored roger
	if (roger->getAnimated() == false) {
		roger->setTexture("assets/art/Roger_bored.png");
		roger->setSource(0, 0, 22, 35);
		roger->setAnimated(
			true,
			Vector2(220, 245),
			10, 7,
			200,
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(9, 6)
		);
	}
	rogerInteraction->setObjectFlag(false);

	if (polly->getPosition().y < 130) { BackroomShade->setPosition(Vector2(900000, 0)); }
	else BackroomShade->setPosition(Vector2(0, 215));

}