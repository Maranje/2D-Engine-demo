#include "title.h"
#include "element.h"
#include "sprite.h"

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
	load();
}

void title::load() {
	Background = new element(sGame);
	Background->setPosition(Vector2(screenWidth / 2, screenHeight / 2));
	background = new sprite(Background, renderer, screenWidth, screenHeight);
	background->setTexture("assets/art/background6.png");

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
}

void title::unload() {
	delete Background;
	delete TitleCard;
	sceneState = inactive;
	sGame->setScene(sGame->Pretitle);
	sGame->load();
}

void title::update() {
	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_RETURN]) runUnload = true;
}