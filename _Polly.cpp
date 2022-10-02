#include "_Polly.h"
#include "sprite.h"
#include "input.h"
#include "camera.h"

_Polly::_Polly(game* Game, SDL_Renderer* Renderer, int SW, int SH, int Scale) : element(Game) {
	fps = 300;

	//load Polly
	setPosition(Vector2((SW / 2), (SH / 2)));
	polly = new sprite(this, Renderer, 26 * Scale, 56 * Scale);
	polly->setTexture("assets/art/Polly_idle_forward.png");
	polly->setSource(0, 0, 26, 56);
	polly->setAnimated(
		true,
		Vector2(182, 448),
		7, 8,
		fps,
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(6, 7)
	);
	pollyCam = new camera(this);

	//set controls
	up = new input(this, SDL_SCANCODE_UP);
	down = new input(this, SDL_SCANCODE_DOWN);
	left = new input(this, SDL_SCANCODE_LEFT);
	right = new input(this, SDL_SCANCODE_RIGHT);
	buttonPress = false;
}

void _Polly::updateElement(float deltaTime) {
	//press keys
	position = getPosition();
	if (up->getPress()) {
		if(!buttonPress){
			polly->setTexture("assets/art/Polly_walk_back.png");
			polly->setSource(0, 0, 26, 56);
			polly->setAnimated(
				true,
				Vector2(104, 56),
				4, 1,
				250,
				Vector2(0, 0),
				Vector2(0, 0),
				Vector2(3, 0)
				);
		}
		position.y -= static_cast<int>(300 * deltaTime);
		buttonPress = true;
	}
	if (down->getPress()) {
		if (!buttonPress) {
			polly->destroyTexture();
			polly->setTexture("assets/art/Polly_walk_forward.png");
			polly->setSource(0, 0, 26, 56);
			polly->setAnimated(
				true,
				Vector2(104, 56),
				4, 1,
				250,
				Vector2(0, 0),
				Vector2(0, 0),
				Vector2(3, 0)
			);
		}
		position.y += static_cast<int>(300 * deltaTime);
		buttonPress = true;
	}
	if (left->getPress()) {
		if (!buttonPress) {
			polly->destroyTexture();
			polly->setTexture("assets/art/Polly_walk_left.png");
			polly->setSource(0, 0, 26, 56);
			polly->setAnimated(
				true,
				Vector2(156, 56),
				6, 1,
				350,
				Vector2(0, 0),
				Vector2(0, 0),
				Vector2(5, 0)
			);
		}
		position.x -= static_cast<int>(400 * deltaTime);
		buttonPress = true;
	}
	if (right->getPress()) {
		if (!buttonPress) {
			polly->destroyTexture();
			polly->setTexture("assets/art/Polly_walk_right.png");
			polly->setSource(0, 0, 26, 56);
			polly->setAnimated(
				true,
				Vector2(156, 56),
				6, 1,
				350,
				Vector2(0, 0),
				Vector2(0, 0),
				Vector2(5, 0)
			);
		}
		position.x += static_cast<int>(400 * deltaTime);
		buttonPress = true;
	}
	setPosition(position);	

	// lift keys
	if (up->getLift()) {
		polly->destroyTexture();
		polly->setTexture("assets/art/Polly_idle_back.png");
		polly->setSource(0, 0, 26, 56);
		polly->setAnimated(
			true,
			Vector2(182, 56),
			7, 1,
			fps,
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(6, 0)
		);
		buttonPress = false;
	}
	if (down->getLift()) {
		polly->destroyTexture();
		polly->setTexture("assets/art/Polly_idle_forward.png");
		polly->setSource(0, 0, 26, 56);
		polly->setAnimated(
			true,
			Vector2(182, 448),
			7, 8,
			fps,
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(6, 7)
		);
		buttonPress = false;
	}
	if (left->getLift()) {
		polly->destroyTexture();
		polly->setTexture("assets/art/Polly_idle_left.png");
		polly->setSource(0, 0, 26, 56);
		polly->setAnimated(
			true,
			Vector2(182, 448),
			7, 8,
			fps,
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(6, 7)
		);
		buttonPress = false;
	}
	if (right->getLift()) {
		polly->destroyTexture();
		polly->setTexture("assets/art/Polly_idle_right.png");
		polly->setSource(0, 0, 26, 56);
		polly->setAnimated(
			true,
			Vector2(182, 448),
			7, 8,
			fps,
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(6, 7)
		);
		buttonPress = false;
	}
}

void _Polly::unload() {

}