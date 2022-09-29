#include "game.h"
#include "element.h"
#include "sprite.h"
#include "camera.h"

game::game() {
	window = nullptr;
	renderer = nullptr;
	Camera = nullptr;

	run = true;
	updatingElements = false;

	event = nullptr;
	keyState = nullptr;

	scale = 2;
	screenWidth = 480 * scale;
	screenHeight = 270 * scale;
	deltaTime = 0.0f;
	ticks = 0;

	scene = Pretitle;
}

game::~game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool game::init() {
	//inistialize SDL video and audio
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//initialize window
	window = SDL_CreateWindow(
		"Pizza Polly",
		30,
		100, 
		screenWidth,
		screenHeight,
		0
	);
	if (!window) {
		SDL_Log("ERROR INITIALIZING WINDOW: %s", SDL_GetError());
		return false;
	}

	//initialize renderer
	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!renderer) {
		SDL_Log("ERROR INITIALIZING RENDERER: %s", SDL_GetError());
		return false;
	}

	//initialize png image
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("ERROR INITIALIZING PNG IMAGE: %s", SDL_GetError());
		return false;
	}

	//initialize camera
	Camera = new SDL_Rect;
	Camera->x = 0;
	Camera->y = 0;
	Camera->w = screenWidth;
	Camera->h = screenHeight;

	//load initial scene
	load();

	return true;
}

void game::runLoop() {
	while (run) {
		processInput();
		update();
		generateOutput();
	}
}

void game::load() {
	element* Logo = new element(this);
	Logo->setPosition(Vector2(screenWidth / 2, screenHeight / 2));
	sprite* logo = new sprite(Logo, renderer, screenWidth, screenHeight);
	logo->setTexture("assets/art/temp_logo.png");
	logo->setSource(0, 0, 480, 270);
	logo->setAnimated(
		true,
		Vector2(2400, 2430),
		5,
		9,
		3000,
		Vector2(0, 0),
		Vector2(4, 8)
	);


	switch (scene) {
	case Pretitle:

		break;

	case Title:

		break;

	case Intro:

		break;

	case RedHerring:
		
		break;
	
	case Test_Area:

		break;
	}
}

/////////////////////////////////////// adders/removers ///////////////////////////////////////

void game::addElement(element* element) {
	//if an element is added while the updateElements function is running, it'll instead
	//be preliminarily added to the pendingElements vector, to be added to the elements vector
	//once all elements have finished updating. this prevents messing up the elements order
	//while iterating through the list
	if (!updatingElements) elements.emplace_back(element);
	else elementCue.emplace_back(element);
}

void game::removeElement(element* element) {
	if (!updatingElements) {
		auto item = std::find(elements.begin(), elements.end(), element);
		if (item != elements.end()) {
			elements.erase(item);
		}
	}
	else elementBin.emplace_back(element);
}

void game::addSprite(sprite* sprite) {
	auto iterate = sprites.begin();
	for (; iterate != sprites.end(); iterate++) {
		if (sprite->getDrawOrder() < (*iterate)->getDrawOrder()) break;
	}
	sprites.insert(iterate, sprite);
}

void game::removeSprite(sprite* sprite) {
	auto item = std::find(sprites.begin(), sprites.end(), sprite);
	if (item != sprites.end()) sprites.erase(item);
}


/////////////////////////////////////////// private ///////////////////////////////////////////

void game::processInput() {	
	//exit on pressing window close button
	event = new SDL_Event;
	while (SDL_PollEvent(event)) {
		if (event->type == SDL_QUIT) run = false;
	}
	delete event;

	//keyboard state pull for closing on escape press
	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE]) run = false;
}

void game::update() {
	generateDeltaTime();

	//update all active elements in scene
	updatingElements = true; //set flag true
	for (auto Element : elements) {
		Element->update(deltaTime);
	}
	updatingElements = false; //set flag false

	//move any elements waiting in the cue to the active list
	for (auto pending : elementCue) {
		elements.emplace_back(pending);
	}
	elementCue.clear(); //clear the element cue

	//remove any elements from the active list that were placed in the bin
	for (auto pending : elementBin) {
		auto Element = std::find(elements.begin(), elements.end(), pending);
		if (Element != elements.end()) elements.erase(Element);
	}
	elementBin.clear();
}

void game::generateOutput() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //set buffer draw color
	SDL_RenderClear(renderer); //clear buffer

	for (auto Sprite : sprites) {
		Sprite->draw();
	}

	SDL_RenderPresent(renderer); //display all textures on buffer
}

void game::generateDeltaTime() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks + 16));
	deltaTime = (SDL_GetTicks() - ticks) / 1000.0f;
	if (deltaTime > 0.05f) deltaTime = 0.05f;
	ticks = SDL_GetTicks();
}