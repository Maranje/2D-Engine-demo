#include "title.h"
#include "element.h"
#include "sprite.h"
#include "input.h"
#include "_Polly.h"
#include <stdlib.h>

title::title(game* Game) : scene(Game) {
	sGame->setCamera(0, 0);
	/*
	* test if need
	Background = nullptr;
	background = nullptr;
	TitleCard = nullptr;
	titleCard = nullptr;
	keyState = nullptr;

	theme = nullptr;
	blit = nullptr;
	blat = nullptr;

	Fade = nullptr;
	fade = nullptr;
	OrderUp = nullptr;
	orderUp = nullptr;
	Polly = nullptr;
	polly = nullptr;

	startInput = nullptr;
	*/
	startBlit = false;
	nextBlit = false;
	lastBlit = false;

	load();
}

void title::load() {
	Background = new element(sGame);
	background = new sprite(Background, 700, 480, Vector2(0, 0), 0);
	background->setTexture("assets/art/background.png");

	for (int i = 0; i < 2; i++) {
		element* Pizza = new element(sGame);
		Pizza->setPosition(Vector2(0, (i * 300)));
		sprite* pizza = new sprite(Pizza, 1651, 300, Vector2(0, 0), 0);
		pizza->setTexture("assets/art/pizza_bckgnd.png");
		pizzas.emplace_back(Pizza);
	}

	TitleCard = new element(sGame);
	titleCard = new sprite(TitleCard, 480, 270, Vector2(0, 0), 0);
	titleCard->setTexture("assets/art/title_card_sheet.png");
	titleCard->setSource(0, 0, 480, 270);
	titleCard->setAnimated(
		true,
		Vector2(1920, 1620),
		4, 6,
		5000,
		Vector2(0, 0),
		Vector2(0, 5),
		Vector2(3, 5)
	);

	//theme music
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	theme = Mix_LoadMUS("assets/audio/music/title_theme.wav");
	Mix_PlayMusic(theme, -1);

	startInput = new input(Background, SDL_SCANCODE_SPACE);

	Fade = new element(sGame);
	fade = new sprite(Fade, 700, 480, Vector2(0, 0), 10);

	OrderUp = new element(sGame);
	orderUp = new sprite(OrderUp, 480, 270, Vector2(0, 0), 11);

	Polly = new element(sGame);
	polly = new sprite(Polly, 26, 55, Vector2(0, 0), 12);

}

void title::unload() {
	for (auto slice : pizzas) delete slice;
	delete Background;
	delete TitleCard;
	delete Fade;
	delete OrderUp;
	delete Polly;
	theme = nullptr;
	Mix_CloseAudio();
	sceneState = inactive;
	sGame->setScene(sGame->RedHerring);
	sGame->load();
}

void title::update(float deltaTime) {
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

	if (startInput->getPress()) {
		Mix_FadeOutMusic(800);
		start();
		startBlit = true;
	}
	if (startBlit) {
		if (!fade->getAnimated()) {
			blitOrderUp();
			nextBlit = true;
			startBlit = false;
		}
	}
	if (nextBlit) {
		if (!orderUp->getAnimated()) {
			blitPolly();
			lastBlit = true;
			nextBlit = false;
		}
	}
	if (lastBlit) {
		if (!polly->getAnimated()) runUnload = true;
	}
}

void title::start() {
	fade->setTexture("assets/art/Fade.png");
	fade->setSource(0, 0, 700, 480);
	fade->setAnimated(
		true,
		Vector2(3500, 960),
		5, 2,
		15000,
		Vector2(0, 0),
		Vector2(4, 1),
		Vector2(4, 1),
		1
	);
}

void title::blitOrderUp() {
	orderUp->setTexture("assets/art/order_up.png");
	orderUp->setSource(0, 0, 480, 270);
	orderUp->setAnimated(
	true,
		Vector2(1920, 1620),
		4, 6,
		7000,
		Vector2(0, 0),
		Vector2(3, 5),
		Vector2(3, 5),
		1
	);
	blat = Mix_LoadWAV("assets/audio/effects/bump.wav");
	Mix_VolumeChunk(blat, 50);
	Mix_PlayChannel(1, blat, 7);
}

void title::blitPolly() {
	blit = Mix_LoadWAV("assets/audio/effects/blit.wav");
	Mix_PlayChannel(1, blit, 0);
	polly->setTexture("assets/art/polly.png");
	polly->setSource(0, 0, 26, 55);
	polly->setAnimated(
		true,
		Vector2(26, 55),
		1, 1,
		120,
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(0, 0),
		2
	);
}