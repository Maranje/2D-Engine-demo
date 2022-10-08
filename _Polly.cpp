#include "_Polly.h"
#include "sprite.h"
#include "input.h"
#include "camera.h"
#include "collider.h"

_Polly::_Polly(game* Game, SDL_Renderer* Renderer, int SW, int SH, float Scale) : element(Game) {
	scale = Scale;

	//load Polly
	setPosition(Vector2((SW / 2), (SH / 2)));
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
	pollyCollider = new collider(this, SW, SH);
	pollyCollider->setCollisionBody(static_cast<int>(16 * scale), 
									static_cast<int>(10 * scale), 
									Vector2(static_cast<int>(0 * scale), static_cast<int>(-22 * scale)));

	//set controls
	up = new input(this, SDL_SCANCODE_UP);
	down = new input(this, SDL_SCANCODE_DOWN);
	left = new input(this, SDL_SCANCODE_LEFT);
	right = new input(this, SDL_SCANCODE_RIGHT);
	move = false;
	currentPressed = 0;
}

void _Polly::updateElement(float deltaTime) {
	//detect collisions... i honestly don't know why this works so well, but it's crucial for it to be before processInput()
	if (pollyCollider->detectCollision()) {
		std::cout << "collision detected" << std::endl;
		move = false;
	}

	processInput(); //process user input
	
	position = getPosition();//get the current position
	if (move) {
		switch (directions[currentPressed - 1]) {
		case Up:
			position.y -= static_cast<int>(91.0f * scale * deltaTime);
			break;
		case Down:
			position.y += static_cast<int>(91.0f * scale * deltaTime);
			break;
		case Left:
			position.x -= static_cast<int>(104.0f * scale * deltaTime);
			break;
		case Right:
			position.x += static_cast<int>(104.0f * scale * deltaTime);
			break;
		}
	}
	//tiny bounce back from collision
	if (pollyCollider->detectCollision()) {
		switch (directions[currentPressed - 1]) {
		case Up:
			position.y += 5;
			break;
		case Down:
			position.y -= 5;
			break;
		case Left:
			position.x += 5;
			break;
		case Right:
			position.x -= 5;
			break;
		}
	}
	setPosition(position); //set new position
}

void _Polly::unload() {
	polly->destroyTexture();
}

void _Polly::processInput() {
	//key presses
	if (up->getPress()) {
		directions.emplace_back(Up);//store respective direction enum in directions vector
		move = true;; // set speed to 1 to activate position movement
		currentPressed++; //increase the number of currently pressed key by one
		setAnimation(); //set respective walk animation
	}
	if (down->getPress()) {
		directions.emplace_back(Down);
		move = true;
		currentPressed++;
		setAnimation();
	}
	if (left->getPress()) {
		directions.emplace_back(Left);
		move = true;
		currentPressed++;
		setAnimation();
	}
	if (right->getPress()) {
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
		else setAnimation();//set to the walk animation of the next most recently pressed key
	}
	if (down->getLift()) {
		auto item = std::find(directions.begin(), directions.end(), Down);
		if (item != directions.end()) directions.erase(item);
		currentPressed--;
		if (currentPressed < 0) currentPressed = 0;
		if (currentPressed == 0) {
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
		else setAnimation();
	}
	if (left->getLift()) {
		auto item = std::find(directions.begin(), directions.end(), Left);
		if (item != directions.end()) directions.erase(item);
		currentPressed--;
		if (currentPressed < 0) currentPressed = 0;
		if (currentPressed == 0) {
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
		else setAnimation();
	}
	if (right->getLift()) {
		auto item = std::find(directions.begin(), directions.end(), Right);
		if (item != directions.end()) directions.erase(item);
		currentPressed--;
		if (currentPressed < 0) currentPressed = 0;
		if (currentPressed == 0) {
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
		else setAnimation();
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