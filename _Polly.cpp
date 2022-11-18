#include "_Polly.h"
#include "sprite.h"
#include "input.h"
#include "camera.h"
#include "interaction.h"
#include "collider.h"

_Polly::_Polly(game* Game) : element(Game) {

	//load Polly
	polly = new sprite(this, 26, 55);
	polly->setTexture("assets/art/Polly_idle_forward.png");
	polly->setSource(0, 0, 26, 55);
	polly->setAnimated(
		true,
		Vector2(182, 440),
		7, 8,
		300,
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(6, 7)
	);
	shadow = new sprite(this, 26, 55);
	shadow->setTexture("assets/art/Polly_shadow.png");
	pollyCam = new camera(this);
	pollyCollider = new collider(this);
	pollyCollider->setCollisionBody(16, 10, Vector2(0, -22));
	pollyAction = new interaction(this);
	pollyAction->setInteractionArea(5, 15, Vector2(0, -15));

	pollySpeed = 91;
	switchInt = 0;
	interact = false;

	//set controls
	action = new input(this, SDL_SCANCODE_SPACE);
	up = new input(this, SDL_SCANCODE_UP);
	down = new input(this, SDL_SCANCODE_DOWN);
	left = new input(this, SDL_SCANCODE_LEFT);
	right = new input(this, SDL_SCANCODE_RIGHT);
	move = false;
	immobile = false;
	carry = false;
	direction = Down;
	currentPressed = 0;
}

void _Polly::updateElement(float deltaTime) {
	//detect collisions
	if (pollyCollider->detectCollision()) {
		move = false;
		
		//bounce back from collision
		switch (direction) {
		case Up:
			increaseVerticalPosition(-91);
			break;
		case Down:
			increaseVerticalPosition(91);
			break;
		case Left:
			increaseHorizontalPosition(91);
			break;
		case Right:
			increaseHorizontalPosition(-91);
			break;
		}
	}

	//set interaction direction
	switch (direction) {
	case Up:
		pollyAction->setInteractionArea(5, 15, Vector2(0, 15));
		break;
	case Down:
		pollyAction->setInteractionArea(5, 15, Vector2(0, -15));
		break;
	case Left:
		pollyAction->setInteractionArea(15, 5, Vector2(15, 0));
		break;
	case Right:
		pollyAction->setInteractionArea(15, 5, Vector2(-15, 0));
		break;
	}

	processInput(); //process user input
	
	//move polly
	if (move) {
		switch (directions[currentPressed - 1]) {
		case Up:
			increaseVerticalPosition(pollySpeed);
			break;
		case Down:
			increaseVerticalPosition(-1 * pollySpeed);
			break;
		case Left:
			increaseHorizontalPosition(-1 * pollySpeed);
			break;
		case Right:
			increaseHorizontalPosition(pollySpeed);
			break;
		}
	}

	//change polly render order to reflect position behind or in front of other objects on map
	polly->setDrawOrderByVerticalPosition();
	polly->updateDrawOrder();
	shadow->setDrawOrderByVerticalPosition(55);
	shadow->updateDrawOrder();
}

void _Polly::unload() {
	polly->destroyTexture();
}

void _Polly::processInput() {
	//interaction detection
	interact = pollyAction->detectInteraction();
	if (action->getPress()) {
		if (interact) pollyAction->setInteractFlag(true);
	}
	else if (action->getLift()) {
		pollyAction->setInteractFlag(false);
	}

	if (!immobile) {
		//arrow key presses
		if (up->getPress()) {
			direction = Up;
			directions.emplace_back(Up);//store respective direction enum in directions vector
			move = true;; // set move to true to activate position movement
			currentPressed++; //increase the number of currently pressed key by one
			setAnimation(); //set respective walk animation
		}
		if (down->getPress()) {
			direction = Down;
			directions.emplace_back(Down);
			move = true;
			currentPressed++;
			setAnimation();
		}
		if (left->getPress()) {
			direction = Left;
			directions.emplace_back(Left);
			move = true;
			currentPressed++;
			setAnimation();
		}
		if (right->getPress()) {
			direction = Right;
			directions.emplace_back(Right);
			move = true;
			currentPressed++;
			setAnimation();
		}
	
		//arrow key lifts
		if (up->getLift()) {
			//find lifted key type and remove it from directions vector
			auto item = std::find(directions.begin(), directions.end(), Up);
			if (item != directions.end()) directions.erase(item);

			currentPressed--; //reduce the number of current keys being pressed
			if (currentPressed < 0) currentPressed = 0; //make sure the number of current keys being pressed is never negative
			//set to respective idle animation if no keys are being currently pressed
			if (currentPressed == 0 && !carry) {
				direction = Up;
				move = false;
			}
			else if (currentPressed == 0 && carry) {
				direction = Up;
				move = false;
			}
			else {
				move = true;
				direction = directions[currentPressed - 1];
			}
			setAnimation();
		}
		if (down->getLift()) {
			auto item = std::find(directions.begin(), directions.end(), Down);
			if (item != directions.end()) directions.erase(item);
			currentPressed--;
			if (currentPressed < 0) currentPressed = 0;
			if (currentPressed == 0 && !carry) {
				direction = Down;
				move = false;
			}
			else if (currentPressed == 0 && carry) {
				direction = Down;
				move = false;
			}
			else {
				move = true;
				direction = directions[currentPressed - 1];
			}
			setAnimation();
		}
		if (left->getLift()) {
			auto item = std::find(directions.begin(), directions.end(), Left);
			if (item != directions.end()) directions.erase(item);
			currentPressed--;
			if (currentPressed < 0) currentPressed = 0;
			if (currentPressed == 0 && !carry) {
				direction = Left;
				move = false;
			}
			else if (currentPressed == 0 && carry) {
				direction = Left;
				move = false;
			}
			else {
				move = true;
				direction = directions[currentPressed - 1];
			}
			setAnimation();
		}
		if (right->getLift()) {
			auto item = std::find(directions.begin(), directions.end(), Right);
			if (item != directions.end()) directions.erase(item);
			currentPressed--;
			if (currentPressed < 0) currentPressed = 0;
			if (currentPressed == 0 && !carry) {
				direction = Right;
				move = false;
			}
			else if (currentPressed == 0 && carry) {
				direction = Right;
				move = false;
			}
			else {//set to the walk animation of the next most recently pressed key
				move = true;
				direction = directions[currentPressed - 1];
			}
			setAnimation();
		}
	}
	//else move = false;
}

bool _Polly::getInteract()
{
	return pollyAction->getInteractFlag();
}

void _Polly::setAnimation() {
	//polly animations when not carrying anything
	if (!carry) {
		//moving
		if (move) {
			switch (directions[currentPressed - 1]) {
			case Up:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_walk_back.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(156, 55),
					6, 1,
					350,
					Vector2(0, 0), Vector2(0, 0), Vector2(5, 0)
				);
				break;
			case Down:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_walk_forward.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(156, 55),
					6, 1,
					350,
					Vector2(0, 0), Vector2(0, 0), Vector2(5, 0)
				);
				break;
			case Left:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_walk_left.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(156, 55),
					6, 1,
					350,
					Vector2(0, 0), Vector2(0, 0), Vector2(5, 0)
				);
				break;
			case Right:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_walk_right.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(156, 55),
					6, 1,
					350,
					Vector2(0, 0), Vector2(0, 0), Vector2(5, 0)
				);
				break;
			}
		}
		//idle
		else {
			if (currentPressed == 0) switchInt = 0; // this bit is neccessary for the animation switch due to interaction so
			else switchInt = currentPressed - 1;    // that it doesn't go below zero but also doesn't pull from the wrong press
			switch (directions[switchInt]) {
			case Up:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_idle_back.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(182, 55),
					7, 1,
					300,
					Vector2(0, 0),
					Vector2(0, 0),
					Vector2(6, 0)
				);
				break;
			case Down:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_idle_forward.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(182, 440),
					7, 8,
					300,
					Vector2(0, 0), Vector2(0, 0), Vector2(6, 7)
				);
				break;
			case Left:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_idle_left.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(182, 440),
					7, 8,
					300,
					Vector2(0, 0), Vector2(0, 0), Vector2(6, 7)
				);
				break;
			case Right:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_idle_right.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(182, 440),
					7, 8,
					300,
					Vector2(0, 0), Vector2(0, 0), Vector2(6, 7)
				);
				break;
			}
		}
	}
	//polly animations when carrying an object
	else {
		//moving
		if (move) {
			switch (directions[currentPressed - 1]) {
			case Up:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_carrywalk_back.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(156, 55),
					6, 1,
					350,
					Vector2(0, 0), Vector2(0, 0), Vector2(5, 0)
				);
				break;
			case Down:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_carrywalk_forward.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(156, 55),
					6, 1,
					350,
					Vector2(0, 0), Vector2(0, 0), Vector2(5, 0)
				);
				break;
			case Left:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_carrywalk_left.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(156, 55),
					6, 1,
					350,
					Vector2(0, 0), Vector2(0, 0), Vector2(5, 0)
				);
				break;
			case Right:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_carrywalk_right.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(156, 55),
					6, 1,
					350,
					Vector2(0, 0), Vector2(0, 0), Vector2(5, 0)
				);
				break;
			}
		}
		//idle
		else {
			if (currentPressed == 0) switchInt = 0;
			else switchInt = currentPressed - 1;
			switch (directions[switchInt]) {
			case Up:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_carry_back.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(182, 55),
					7, 1,
					300,
					Vector2(0, 0),
					Vector2(0, 0),
					Vector2(6, 0)
				);
				break;
			case Down:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_carry_forward.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(182, 55),
					7, 1,
					300,
					Vector2(0, 0), Vector2(0, 0), Vector2(6, 0)
				);
				break;
			case Left:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_carry_left.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(182, 55),
					7, 1,
					300,
					Vector2(0, 0), Vector2(0, 0), Vector2(6, 0)
				);
				break;
			case Right:
				polly->destroyTexture();
				polly->setTexture("assets/art/Polly_carry_right.png");
				polly->setSource(0, 0, 26, 55);
				polly->setAnimated(
					true,
					Vector2(182, 55),
					7, 1,
					300,
					Vector2(0, 0), Vector2(0, 0), Vector2(6, 0)
				);
				break;
			}
		}
	}
}