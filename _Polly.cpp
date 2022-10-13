#include "_Polly.h"
#include "sprite.h"
#include "input.h"
#include "camera.h"
#include "collider.h"

_Polly::_Polly(game* Game, SDL_Renderer* Renderer, float Scale) : element(Game) {
	scale = Scale;

	//load Polly
	polly = new sprite(this, Renderer, static_cast<int>(26.0f * scale), static_cast<int>(56.0f * scale));
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
	pollyCam = new camera(this);
	pollyCollider = new collider(this);
	pollyCollider->setCollisionBody(static_cast<int>(16 * scale), 
									static_cast<int>(10 * scale), 
									Vector2(static_cast<int>(0 * scale), static_cast<int>(-22 * scale)));

	//set controls
	up = new input(this, SDL_SCANCODE_UP);
	down = new input(this, SDL_SCANCODE_DOWN);
	left = new input(this, SDL_SCANCODE_LEFT);
	right = new input(this, SDL_SCANCODE_RIGHT);
	move = false;
	direction = Down;
	currentPressed = 0;
}

void _Polly::updateElement(float deltaTime) {
	processInput(); //process user input

	//detect collisions
	if (pollyCollider->detectCollision()) {
		std::cout << "collision detected" << std::endl;
		move = false;

		//bounce back from collision
		switch (direction) {
		case Up:
			increaseVerticalPosition(static_cast<int>(-91.0f * scale * deltaTime));
			break;
		case Down:
			increaseVerticalPosition(static_cast<int>(91.0f * scale * deltaTime));
			break;
		case Left:
			increaseHorizontalPosition(static_cast<int>(91.0f * scale * deltaTime));
			break;
		case Right:
			increaseHorizontalPosition(static_cast<int>(-91.0f * scale * deltaTime));
			break;
		}
	}
	
	if (move) {
		switch (directions[currentPressed - 1]) {
		case Up:
			increaseVerticalPosition(static_cast<int>(91.0f * scale * deltaTime));
			break;
		case Down:
			increaseVerticalPosition(static_cast<int>(-91.0f * scale * deltaTime));
			break;
		case Left:
			increaseHorizontalPosition(static_cast<int>(-91.0f * scale * deltaTime));
			break;
		case Right:
			increaseHorizontalPosition(static_cast<int>(91.0f * scale * deltaTime));
			break;
		}
	}
}

void _Polly::unload() {
	polly->destroyTexture();
}

void _Polly::processInput() {
	//key presses
	if (up->getPress()) {
		direction = Up;
		directions.emplace_back(Up);//store respective direction enum in directions vector
		move = true;; // set speed to 1 to activate position movement
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
	//key lifts
	if (up->getLift()) {
		//find lifted key type and remove it from directions vector
		auto item = std::find(directions.begin(), directions.end(), Up);
		if (item != directions.end()) directions.erase(item);

		currentPressed--; //reduce the number of current keys being pressed
		if (currentPressed < 0) currentPressed = 0; //make sure the number of current keys being pressed is never negative
		//set to respective idle animation if no keys are being currently pressed
		if (currentPressed == 0) {
			direction = Up;
			move = false;
			polly->destroyTexture();
			polly->setTexture("assets/art/Polly_idle_back.png");
			polly->setSource(0, 0, 26, 55);
			polly->setAnimated(
				true,
				Vector2(182, 55),
				7, 1,
				300,
				Vector2(0, 0), Vector2(0, 0), Vector2(6, 0)
			);
		}
		else {
			move = true;
			direction = directions[currentPressed - 1];
			setAnimation();//set to the walk animation of the next most recently pressed key
		}
	}
	if (down->getLift()) {
		auto item = std::find(directions.begin(), directions.end(), Down);
		if (item != directions.end()) directions.erase(item);
		currentPressed--;
		if (currentPressed < 0) currentPressed = 0;
		if (currentPressed == 0) {
			direction = Down;
			move = false;
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
		}
		else {
			move = true;
			direction = directions[currentPressed - 1];
			setAnimation();//set to the walk animation of the next most recently pressed key
		}
	}
	if (left->getLift()) {
		auto item = std::find(directions.begin(), directions.end(), Left);
		if (item != directions.end()) directions.erase(item);
		currentPressed--;
		if (currentPressed < 0) currentPressed = 0;
		if (currentPressed == 0) {
			direction = Left;
			move = false;
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
		}
		else {
			move = true;
			direction = directions[currentPressed - 1];
			setAnimation();//set to the walk animation of the next most recently pressed key
		}
	}
	if (right->getLift()) {
		auto item = std::find(directions.begin(), directions.end(), Right);
		if (item != directions.end()) directions.erase(item);
		currentPressed--;
		if (currentPressed < 0) currentPressed = 0;
		if (currentPressed == 0) {
			direction = Right;
			move = false;
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
		}
		else {
			move = true;
			direction = directions[currentPressed - 1];
			setAnimation();//set to the walk animation of the next most recently pressed key
		}
	}
}

void _Polly::setAnimation() {
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