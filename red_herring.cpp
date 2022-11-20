#include "red_herring.h"
#include "_Polly.h"
#include "input.h"
#include "element.h"
#include "sprite.h"
#include "collider.h"
#include "interaction.h"
#include "camera.h"

red_herring::red_herring(game* Game) : scene(Game) {
	//music
	//theme = nullptr;

	//bools
	rogerSleep = false;
	label = false;
	pollySouth = true;

	//////////////////////////////game objects///////////////////////////////// (might not need this part)
	/*
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

	Roger = nullptr;
	roger = nullptr;
	rogerBody = nullptr;
	rogerInteraction = nullptr;

	Wall = nullptr;
	wall = nullptr;
	wallBody = nullptr;

	Mat = nullptr;
	mat = nullptr;

	Ingredients = nullptr;
	ingredients = nullptr;
	ingredientsBody = nullptr;
	bc = nullptr;
	bo = nullptr;
	gp = nullptr;
	p = nullptr;
	pi = nullptr;
	s = nullptr;
	h = nullptr;
	c = nullptr;

	Mop = nullptr;
	mop = nullptr;
	mopBody = nullptr;

	Box = nullptr;
	box = nullptr;
	boxBody = nullptr;

	Wall2 = nullptr;
	wall2 = nullptr;
	wall2Body = nullptr;

	CRT = nullptr;
	crt = nullptr;

	Door = nullptr;
	door = nullptr;

	Can = nullptr;
	can = nullptr;
	canBody = nullptr;

	SealedStack = nullptr;
	sealedStack = nullptr;
	sealedStackBody = nullptr;
	*/

	load();
}

void red_herring::load() {
	//play music
	Mix_OpenAudio(22050, AUDIO_S16SYS, 4, 4096);
	Mix_VolumeMusic(30);
	theme = Mix_LoadMUS("assets/audio/music/pizza_theme.wav");
	Mix_PlayMusic(theme, -1);
	flup = Mix_LoadWAV("assets/audio/effects/flup.wav");
	dump = Mix_LoadWAV("assets/audio/effects/dump.wav");

	polly = new _Polly(sGame);
	polly->getPollyCam()->cameraHaltX(true);
	exit = new input(polly, SDL_SCANCODE_RETURN);

	pizzaStage = free;

	Background = new element(sGame);
	background = new sprite(Background, 700, 480);
	background->setTexture("assets/art/background.png");
	background->setCameraNeutral();

	//floating background pizzas
	for (int i = 0; i < 2; i++) {
		element* Pizza = new element(sGame);
		Pizza->setPosition(Vector2(0, (i * 300)));
		sprite* pizza = new sprite(Pizza, 1651, 300);
		pizza->setTexture("assets/art/pizza_bckgnd.png");
		pizza->setCameraNeutral();
		pizzas.emplace_back(Pizza);
	}

	//floor and wall boundaries
	Floor = new element(sGame);
	floor = new sprite(Floor, 190, 577);
	floor->setTexture("assets/art/pizza_floor.png");
	boundN = new collider(Floor);
	boundN->setCollisionBody(172, 10, Vector2(0, 279));
	boundS = new collider(Floor);
	boundS->setCollisionBody(172, 10, Vector2(0, -279));
	boundE = new collider(Floor);
	boundE->setCollisionBody(10, 559, Vector2(86, 0));
	boundW = new collider(Floor);
	boundW->setCollisionBody(10, 559, Vector2(-86, 0));

	//front counter
	Counter = new element(sGame);
	Counter->setPosition(Vector2(0, -180));
	counter = new sprite(Counter, 165, 85);
	counter->setDrawOrderByVerticalPosition();
	counter->updateDrawOrder();
	counter->setTexture("assets/art/front_counter.png");
	counterBody = new collider(Counter);
	counterBody->setCollisionBody(165, 22, Vector2(0, -32));

	DoughStack = new element(sGame);
	DoughStack->setPosition(Vector2(-60, -90));
	doughStack = new sprite(DoughStack, 49, 50);
	doughStack->setDrawOrderByVerticalPosition(25);
	doughStack->updateDrawOrder();
	doughStack->setTexture("assets/art/dough_stack.png");
	doughStackBody = new collider(DoughStack);
	doughStackBody->setCollisionBody(49, 30, Vector2(0, -11));
	dough = new interaction(DoughStack);
	dough->setInteractionArea(40, 40);

	TrayStation = new element(sGame);
	TrayStation->setPosition(Vector2(-64, 0));
	trayStation = new sprite(TrayStation, 43, 56);
	trayStation->setDrawOrderByVerticalPosition(25);
	trayStation->updateDrawOrder();
	trayStation->setTexture("assets/art/tray_station.png");
	trayStationBody = new collider(TrayStation);
	trayStationBody->setCollisionBody(44, 30, Vector2(0, -11));

	FlourStation = new element(sGame);
	FlourStation->setPosition(Vector2(-64, -37));
	flourStation = new sprite(FlourStation, 44, 55);
	flourStation->setDrawOrderByVerticalPosition(25);
	flourStation->updateDrawOrder();
	flourStation->setTexture("assets/art/flour_station.png");
	flourStationBody = new collider(FlourStation);
	flourStationBody->setCollisionBody(44, 30, Vector2(0, -11));
	flatten = new interaction(FlourStation);
	flatten->setInteractionArea(30, 10, Vector2(0, 16));
	flattens = 0;

	//two oven components
	OvenMain = new element(sGame);
	OvenBelt = new element(sGame);
	OvenMain->setPosition(Vector2(10, 75));
	OvenBelt->setPosition(Vector2(10, 68));
	ovenMain = new sprite(OvenMain, 59, 63);
	ovenMain->setDrawOrderByVerticalPosition();
	ovenMain->updateDrawOrder();
	ovenMain->setTexture("assets/art/oven_mainbody.png");
	ovenMainBody = new collider(OvenMain);
	ovenMainBody->setCollisionBody(59, 30, Vector2(0, -11));
	ovenBelt = new sprite(OvenBelt, 85, 40);
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

	//Roger
	Roger = new element(sGame);
	Roger->setPosition(Vector2(60, -166));
	roger = new sprite(Roger, 22, 35);
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
	rogerInteraction->setInteractionArea(22, 35);

	// dividing wall
	Wall = new element(sGame);
	Wall->setPosition(Vector2(0, 117));
	wall = new sprite(Wall, 170, 81);
	wall->setTexture("assets/art/Back_wall.png");
	wall->setDrawOrderByVerticalPosition(-10);
	wall->updateDrawOrder();
	wallBody = new collider(Wall);
	wallBody->setCollisionBody(125, 28, Vector2(20, -22));
	wallBody = new collider(Wall);
	wallBody->setCollisionBody(15, 34, Vector2(-74, -26));

	//ingredients bar
	Ingredients = new element(sGame);
	Ingredients->setPosition(Vector2(64, -45));
	ingredients = new sprite(Ingredients, 41, 153);
	ingredients->setTexture("assets/art/ing_station.png");
	ingredients->setDrawOrderByVerticalPosition(80);
	ingredients->updateDrawOrder();
	ingredientsBody = new collider(Ingredients);
	ingredientsBody->setCollisionBody(41, 134, Vector2(-2, -11));
	ingredientsAct = new interaction(Ingredients);
	ingredientsAct->setInteractionArea(10, 123, Vector2(5, 15));
	ingredient = new sprite(Ingredients, 61, 14, Vector2(0, 0), 1000000);
	ingredient->setSource(0, 0, 81, 19);


	Mop = new element(sGame);
	Mop->setPosition(Vector2(-71, 200));
	mop = new sprite(Mop, 28, 64);
	mop->setTexture("assets/art/bucket_mop.png");
	mop->setDrawOrderByVerticalPosition();
	mop->updateDrawOrder();
	mopBody = new collider(Mop);
	mopBody->setCollisionBody(28, 20, Vector2(0, -22));

	Box = new element(sGame);
	Box->setPosition(Vector2(-63, 198));
	box = new sprite(Box, 45, 29);
	box->setTexture("assets/art/box.png");
	box->setDrawOrderByVerticalPosition(30);
	box->updateDrawOrder();
	boxBody = new collider(Box);
	boxBody->setCollisionBody(45, 20, Vector2(0, -2));

	Wall2 = new element(sGame);
	Wall2->setPosition(Vector2(0, 242));
	wall2 = new sprite(Wall2, 170, 74);
	wall2->setTexture("assets/art/Exit_wall.png");
	wall2->setDrawOrderByVerticalPosition();
	wall2->updateDrawOrder();
	wall2Body = new collider(Wall2);
	wall2Body->setCollisionBody(170, 73);

	CRT = new element(sGame);
	CRT->setPosition(Vector2(-7, 124));
	crt = new sprite(CRT, 26, 45);
	crt->setTexture("assets/art/crt.png");
	crt->setDrawOrderByVerticalPosition(-70);
	crt->updateDrawOrder();
	crt->setSource(0, 0, 26, 45);
	crt->setAnimated(
		true,
		Vector2(598, 450),
		23, 10,
		130,
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(22, 9)
	);

	Door = new element(sGame);
	Door->setPosition(Vector2(-56, 106));
	door = new sprite(Door, 32, 82);
	door->setDrawOrderByVerticalPosition(10);
	door->updateDrawOrder();
	door->setTexture("assets/art/Door.png");
	door->setSource(0, 0, 32, 82);

	Can = new element(sGame);
	Can->setPosition(Vector2(-26, 210));
	can = new sprite(Can, 33, 40);
	can->setTexture("assets/art/Can.png");
	can->setDrawOrderByVerticalPosition(15);
	can->updateDrawOrder();
	canBody = new collider(Can);
	canBody->setCollisionBody(33, 14, Vector2(0, -13));
	trash = new interaction(Can);
	trash->setInteractionArea(10, 10, Vector2(0, 14));

	SealedStack = new element(sGame);
	SealedStack->setPosition(Vector2(60, 177));
	sealedStack = new sprite(SealedStack, 51, 51);
	sealedStack->setDrawOrderByVerticalPosition(20);
	sealedStack->updateDrawOrder();
	sealedStack->setTexture("assets/art/dough_stack_sealed.png");
	sealedStackBody = new collider(SealedStack);
	sealedStackBody->setCollisionBody(51, 30, Vector2(0, -11));

}

void red_herring::unload() {
	delete polly;
	delete Background;	
	delete Floor;
	delete Counter;
	delete DoughStack;
	delete FlourStation;
	delete TrayStation;
	delete OvenMain;
	delete OvenBelt;
	delete Roger;
	delete Wall;
	delete Ingredients;
	delete Mop;
	delete Box;
	delete Wall2;
	delete CRT;
	delete Door;
	delete Can;
	delete SealedStack;
	for (auto slice : pizzas) delete slice;
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
	if (roger->getRuns() == 2 && rogerSleep == false) {
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
	else if (rogerInteraction->getInstanceInteractFlag() && rogerSleep == true) {
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
	}
	//normal bored roger
	else if (roger->getAnimated() == false) {
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

	//door
	if (pollySouth) {
		//polly opens door up
		if (polly->getScaledPosition().y <= 36 && polly->getScaledPosition().y > 15) {
			polly->setPollySpeed(75);
			if (polly->getScaledPosition().y <= 36 && polly->getScaledPosition().y >= 34) {
				door->haltAnimation();
				door->setSource(0, 82, 32, 82);
			}
			else if (polly->getScaledPosition().y < 34 && polly->getScaledPosition().y > 32) door->setSource(32, 82, 32, 82);
			else if (polly->getScaledPosition().y < 32 && polly->getScaledPosition().y > 30) door->setSource(64, 82, 32, 82);
			else if (polly->getScaledPosition().y < 30 && polly->getScaledPosition().y > 27) door->setSource(96, 82, 32, 82);
			else if (polly->getScaledPosition().y < 27 && polly->getScaledPosition().y > 22) door->setSource(128, 82, 32, 82);
			else if (polly->getScaledPosition().y < 22 && polly->getScaledPosition().y > 19) door->setSource(160, 82, 32, 82);
			else if (polly->getScaledPosition().y < 19 && polly->getScaledPosition().y > 15) door->setSource(192, 82, 32, 82);
		}
		//door shuts
		else if (polly->getScaledPosition().y <= 15) {
			polly->setPollySpeed(91);
			door->setAnimated(
				true,
				Vector2(576, 164),
				18, 2,
				500,
				Vector2(6, 1),
				Vector2(17, 1),
				Vector2(17, 1),
				1
			);
			pollySouth = false;
		}
		else if (polly->getPollySpeed() != 91) polly->setPollySpeed(91);
	}
	else{
		//polly opens door down
		if (polly->getScaledPosition().y > 15 && polly->getScaledPosition().y < 44) {
			polly->setPollySpeed(75);
			door->setDrawOrderByVerticalPosition(-20);
			door->updateDrawOrder();
			if (polly->getScaledPosition().y >= 27 && polly->getScaledPosition().y <= 29) {
				door->haltAnimation();
				door->setSource(0, 0, 32, 82);
			}
			else if (polly->getScaledPosition().y > 26 && polly->getScaledPosition().y < 27) door->setSource(32, 0, 32, 82);
			else if (polly->getScaledPosition().y < 29 && polly->getScaledPosition().y > 27) door->setSource(64, 0, 32, 82);
			else if (polly->getScaledPosition().y < 32 && polly->getScaledPosition().y > 29) door->setSource(96, 0, 32, 82);
			else if (polly->getScaledPosition().y < 37 && polly->getScaledPosition().y > 32) door->setSource(128, 0, 32, 82);
			else if (polly->getScaledPosition().y < 40 && polly->getScaledPosition().y > 37) door->setSource(160, 0, 32, 82);
			else if (polly->getScaledPosition().y < 44 && polly->getScaledPosition().y > 40) door->setSource(192, 0, 32, 82);
		}
		//door shuts
		else if (polly->getScaledPosition().y >= 44) {
			polly->setPollySpeed(91);
			door->setAnimated(
				true,
				Vector2(576, 164),
				18, 2,
				500,
				Vector2(6, 0),
				Vector2(17, 0),
				Vector2(17, 0),
				1
			);
			pollySouth = true;
			door->setDrawOrderByVerticalPosition(10);
			door->updateDrawOrder();
		}
		else if (polly->getPollySpeed() != 91) polly->setPollySpeed(91);
	}

	//grab dough and initiate pizza making sequence
	if (dough->getInstanceInteractFlag() && pizzaStage == free) {
		Mix_PlayChannel(1, flup, 0);
		polly->setCarry(true);
		polly->setAnimation();
		pizzaStage = doughStage;
		pizza = new sprite(polly, 15, 11, Vector2(-11, -2));
		pizza->setTexture("assets/art/Dough.png");
	}

	//update the orientation of pizza according to polly direction
	if (polly->getCarry()) {
		switch (polly->getDirection()) {
		case 0: //up
			pizza->setOffset(Vector2(0, -5));
			pizza->setDrawOrderByVerticalPosition(1);
			pizza->updateDrawOrder();
			break;
		case 1: //down
			pizza->setOffset(Vector2(0, -6));
			pizza->setDrawOrderByVerticalPosition(-1);
			pizza->updateDrawOrder();
			break;
		case 2: //left
			pizza->setOffset(Vector2(-11, -2));
			pizza->setDrawOrderByVerticalPosition(1);
			pizza->updateDrawOrder();
			break;
		case 3: //right
			pizza->setOffset(Vector2(11, -2));
			pizza->setDrawOrderByVerticalPosition(1);
			pizza->updateDrawOrder();
			break;
		}
	}
	
	//flour station dough flattening
	if (flatten->getInstanceInteractFlag() && pizzaStage == doughStage && polly->getDirection() == 2 && !pizza->getAnimated()) {
		switch (flattens) {
		case 0:
			polly->setCarry(false);
			polly->setAnimation();
			delete pizza;
			pizza = new sprite(FlourStation, 15, 11, Vector2(10, 11));
			pizza->setDrawOrderByVerticalPosition(-20);
			pizza->updateDrawOrder();
			pizza->setTexture("assets/art/DoughAnim.png");
			pizza->setSource(0, 0, 15, 11);
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 0),
				Vector2(0, 0),
				Vector2(3, 0),
				1
			);
			flattens++;
			break;
		case 1:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 0),
				Vector2(0, 0),
				Vector2(3, 0),
				1
			);
			flattens++;
			break;
		case 2:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 0),
				Vector2(0, 0),
				Vector2(3, 0),
				1
			);
			flattens++;
			break;
		case 3:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 0),
				Vector2(0, 0),
				Vector2(3, 0),
				1
			);
			flattens++;
			break;
		case 4:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 1),
				Vector2(0, 1),
				Vector2(3, 1),
				1
			);
			flattens++;
			break;
		case 5:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 1),
				Vector2(0, 1),
				Vector2(3, 1),
				1
			);
			flattens++;
			break;
		case 6:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 1),
				Vector2(0, 1),
				Vector2(3, 1),
				1
			);
			flattens++;
			break;
		case 7:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 1),
				Vector2(0, 1),
				Vector2(3, 1),
				1
			);
			flattens++;
			break;
		case 8:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 2),
				Vector2(0, 2),
				Vector2(3, 2),
				1
			);
			flattens++;
			break;
		case 9:
			pizza->setAnimated(
				true,
				Vector2(60, 33),
				4, 3,
				300,
				Vector2(0, 2),
				Vector2(0, 2),
				Vector2(3, 2),
				1
			);
			flattens++;
			break;
		case 10:
			delete pizza;
			pizza = new sprite(FlourStation, 17, 8, Vector2(10, 9));
			pizza->setDrawOrderByVerticalPosition(-20);
			pizza->updateDrawOrder();
			pizza->setTexture("assets/art/RawZa.png");
			flattens++;
			break;
		case 11:
			polly->setImmobile(false);
			polly->setCarry(true);
			polly->setAnimation();
			delete pizza;
			pizza = new sprite(polly, 17, 8, Vector2(-11, -2));
			pizza->setDrawOrderByVerticalPosition(-20);
			pizza->updateDrawOrder();
			pizza->setTexture("assets/art/RawZa.png");
			pizzaStage = prepStage;
			flattens = 0;
			break;
		}
	}

	//ingredients bar
	if (ingredientsAct->getObjectFlag() && polly->getDirection() == 3) {
		switch (static_cast<int>((polly->getScaledPosition().y - 101) / 16)) {
		case 0: //black olives
			if (!label) {
				ingredient->setOffset(Vector2(10, 75));
				ingredient->setTexture("assets/art/labels/label_bo.png");
			}
			else if (ingredientsAct->getInstanceInteractFlag() && pizzaStage == prepStage) {
				pizza->updateTexture("assets/art/BlackOlives.png", 8);
			}
			break;
		case 1: //pineapple
			if (!label) {
				ingredient->setOffset(Vector2(10, 59));
				ingredient->setTexture("assets/art/labels/label_pi.png");
			}
			else if (ingredientsAct->getInstanceInteractFlag() && pizzaStage == prepStage) {
				pizza->updateTexture("assets/art/Pineapple.png", 7);
			}
			break;
		case 2: //green peppers
			if (!label) {
				ingredient->setOffset(Vector2(10, 43));
				ingredient->setTexture("assets/art/labels/label_gp.png");
			}
			else if (ingredientsAct->getInstanceInteractFlag() && pizzaStage == prepStage) {
				pizza->updateTexture("assets/art/GreenPeppers.png", 6);
			}
			break;
		case 3: //buffalo chicken
			if (!label) {
				ingredient->setOffset(Vector2(10, 27));
				ingredient->setTexture("assets/art/labels/label_bc.png");
			}
			else if (ingredientsAct->getInstanceInteractFlag() && pizzaStage == prepStage) {
				pizza->updateTexture("assets/art/BuffaloChicken.png", 3);
			}
			break;
		case 4: //ham
			if (!label) {
				ingredient->setOffset(Vector2(10, 11));
				ingredient->setTexture("assets/art/labels/label_h.png");
			}
			else if (ingredientsAct->getInstanceInteractFlag() && pizzaStage == prepStage) {
				pizza->updateTexture("assets/art/Ham.png", 5);
			}
			break;
		case 5: //pepperoni
			if (!label) {
				ingredient->setOffset(Vector2(10, -5));
				ingredient->setTexture("assets/art/labels/label_p.png");
			}
			else if (ingredientsAct->getInstanceInteractFlag() && pizzaStage == prepStage) {
				pizza->updateTexture("assets/art/Pepperoni.png", 4);
			}
			break;
		case 6: //cheese
			if (!label) {
				ingredient->setOffset(Vector2(10, -21));
				ingredient->setTexture("assets/art/labels/label_c.png");
			}
			else if (ingredientsAct->getInstanceInteractFlag() && pizzaStage == prepStage) {
				pizza->updateTexture("assets/art/Cheese.png", 2);
			}
			break;
		case 7: //sauce
			if (!label) {
				ingredient->setOffset(Vector2(10, -37));
				ingredient->setTexture("assets/art/labels/label_s.png");
			}
			else if (ingredientsAct->getInstanceInteractFlag() && pizzaStage == prepStage) {
				pizza->updateTexture("assets/art/Sauce.png", 1);
			}
			break;
		}
		if (!label) {
			ingredient->setAnimated(
				true,
				Vector2(65, 190),
				1, 10,
				1500,
				Vector2(0, 0),
				Vector2(0, 5),
				Vector2(0, 5),
				1
			);
			label = true;
		}
	}
	else if (label && !ingredientsAct->getObjectFlag()) {
		ingredient->setAnimated(
			true,
			Vector2(65, 190),
			1, 10,
			1500,
			Vector2(0, 5),
			Vector2(0, 0),
			Vector2(0, 9),
			1
		);
		label = false;
	}

	//toss out
	if (trash->getInstanceInteractFlag() && polly->getCarry()) {
		Mix_PlayChannel(1, dump, 0);
		polly->setCarry(false);
		polly->setAnimation();
		delete pizza;
		pizzaStage = free;
	}
} 