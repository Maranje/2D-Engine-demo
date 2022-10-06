#include "title.h"
#include "element.h"
#include "sprite.h"
#include "input.h"
#include "_Polly.h"
#include <stdlib.h>

title::title(game* Game, SDL_Renderer* Renderer, int SW, int SH, float Scale) : scene(Game) {
	renderer = Renderer;
	screenWidth = SW;
	screenHeight = SH;
	scale = Scale;

	sGame->setCamera(0, 0);

	Background = nullptr;
	background = nullptr;
	TitleCard = nullptr;
	titleCard = nullptr;
	keyState = nullptr;
	theme = nullptr;

	startInput = nullptr;

	load();
}

void title::load() {
	Background = new element(sGame);
	Background->setPosition(Vector2(screenWidth / 2, screenHeight / 2));
	background = new sprite(Background, renderer, static_cast<int>(480.0f * scale), static_cast<int>(480.0f * scale), 0);
	background->setTexture("assets/art/background.png");

	for (int i = 0; i < 2; i++) {
		element* Pizza = new element(sGame);
		Pizza->setPosition(Vector2(0, ((300 * scale) / 2) - (i * (300 * scale))));
		sprite* pizza = new sprite(Pizza, renderer, static_cast<int>(1651.0f * scale), static_cast<int>(300.0f * scale), 0);
		pizza->setTexture("assets/art/pizza_bckgnd.png");
		pizzas.emplace_back(Pizza);
	}

	TitleCard = new element(sGame);
	TitleCard->setPosition(Vector2(screenWidth / 2, screenHeight / 2));
	titleCard = new sprite(TitleCard, renderer, static_cast<int>(480.0f * scale), static_cast<int>(270.0f * scale), 0);
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

}

void title::unload() {
	for (auto slice : pizzas) delete slice;
	delete Background;
	delete TitleCard;
	theme = nullptr;
	Mix_CloseAudio();
	sceneState = inactive;
	sGame->setScene(sGame->Test_Area);
	sGame->load();
}

void title::update(float deltaTime) {
	for (auto slice : pizzas) {
		Vector2 position = slice->getPosition();
		position.x += static_cast<int>(19.0f * scale * deltaTime);
		position.y += static_cast<int>(19.0f * scale * deltaTime);
		if (position.y > 450 * scale) {
			slice->setPosition(Vector2(0, 0 - (150 * scale)));
		}
		else slice->setPosition(position);
	}

	if (startInput->getPress()) runUnload = true;
}