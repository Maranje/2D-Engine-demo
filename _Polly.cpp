#include "_Polly.h"
#include "sprite.h"
#include "input.h"

_Polly::_Polly(game* Game, SDL_Renderer* Renderer, int SW, int SH, int Scale) : element(Game) {
	fps = 200;

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

	//set controls
	up = new input(this, SDL_SCANCODE_UP);
	down = new input(this, SDL_SCANCODE_DOWN);
	left = new input(this, SDL_SCANCODE_LEFT);
	right = new input(this, SDL_SCANCODE_RIGHT);
}

void _Polly::updateElement(float deltaTime) {
	if (up->getLift()) {
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
	}
	if (down->getLift()) {
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
	}
	if (left->getLift()) {
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
	}
	if (right->getLift()) {
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
	}
}

void _Polly::unload() {

}