#include "title.h"
#include "element.h"
#include "sprite.h"
#include <stdlib.h>

title::title(game* Game, SDL_Renderer* Renderer, int SW, int SH, int Scale) : scene(Game) {
	renderer = Renderer;
	screenWidth = SW;
	screenHeight = SH;
	scale = Scale;

	Background = nullptr;
	background = nullptr;
	TitleCard = nullptr;
	titleCard = nullptr;
	keyState = nullptr;
	theme = nullptr;
	load();
}

void title::load() {
	Background = new element(sGame);
	Background->setPosition(Vector2(screenWidth / 2, screenHeight / 2));
	background = new sprite(Background, renderer, screenWidth, screenHeight);
	background->setTexture("assets/art/background6.png");

	for (int i = 0; i < 2; i++) {
		element* Pizza = new element(sGame);
		Pizza->setPosition(Vector2(0, (screenHeight/2) - (i * screenHeight)));
		sprite* pizza = new sprite(Pizza, renderer, 1651 * scale, 270 * scale);
		pizza->setTexture("assets/art/pizza_bckgnd.png");
		pizzas.emplace_back(Pizza);
	}

	TitleCard = new element(sGame);
	TitleCard->setPosition(Vector2(screenWidth / 2, screenHeight / 2));
	titleCard = new sprite(TitleCard, renderer, screenWidth, screenHeight);
	titleCard->setTexture("assets/art/title_card_sheet.png");
	titleCard->setSource(0, 0, 480, 270);
	titleCard->setAnimated(
		true,
		Vector2(2400, 1350),
		5, 5,
		5000,
		Vector2(0, 0),
		Vector2(0, 4),
		Vector2(4, 4)
	);

	//theme music
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	theme = Mix_LoadMUS("assets/audio/music/title_theme.wav");
	Mix_PlayMusic(theme, -1);

}

void title::unload() {
	for (auto slice : pizzas) delete slice;
	delete Background;
	delete TitleCard;
	theme = nullptr;
	Mix_CloseAudio();
	sceneState = inactive;
	sGame->setScene(sGame->Pretitle);
	sGame->load();
}

void title::update(float deltaTime) {
	for (auto slice : pizzas) {
		Vector2 position = slice->getPosition();
		position.x += static_cast<int>(100.0f * deltaTime);
		position.y += static_cast<int>(100.0f * deltaTime);
		if (position.y > screenHeight + (screenHeight/2)) {
			slice->setPosition(Vector2(0, 0 - (screenHeight / 2)));
		}
		else slice->setPosition(position);
	}
	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_RETURN]) runUnload = true;
}