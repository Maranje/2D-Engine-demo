#include "game.h"
#include "element.h"

game::game() {
	window = nullptr;
	renderer = nullptr;

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
		100,
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

	//initiate png image
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("ERROR INITIALIZING PNG IMAGE: %s", SDL_GetError());
		return false;
	}

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
	if (!updatingElements) elements.emplace_back(element);
	else elementCue.emplace_back(element);
}

void game::removeElement(element* element) {
	auto item = std::find(elements.begin(), elements.end(), element);
	if (item != elements.end()) elements.erase(item);
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

	//update all active elements in scene, remove any inactive elements that slipped under the radar
	updatingElements = true; //set flag true
	for (auto Element : elements) {
		if (Element->getState() == Element->inactive) removeElement(Element);
		else Element->update(deltaTime);
	}
	updatingElements = false; //set flag false
	//move any elements waiting in the cue to the active list
	for (auto pending : elementCue) {
		elements.emplace_back(pending);
	}
	elementCue.clear(); //clear the element cue
}

void game::generateOutput() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //set buffer draw color
	SDL_RenderClear(renderer); //clear buffer

	SDL_RenderPresent(renderer); //display all textures on buffer
}

void game::generateDeltaTime() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks + 16));
	deltaTime = (SDL_GetTicks() - ticks) / 1000.0f;
	if (deltaTime > 0.05f) deltaTime = 0.05f;
	ticks = SDL_GetTicks();
}