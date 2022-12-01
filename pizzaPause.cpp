#include "pizzaPause.h"
#include "element.h"
#include "input.h"

pizzaPause::pizzaPause(class game* Game, class element* Owner, class input* ESC) : pause(Game){
	owner = Owner;
	enter = new input(owner, SDL_SCANCODE_RETURN);
	up = new input(owner, SDL_SCANCODE_UP);
	down = new input(owner, SDL_SCANCODE_DOWN);
	esc = ESC;
	run = false;

	//MenuScreen = new element(pGame);
}

pizzaPause::~pizzaPause() {
	
}

void pizzaPause::runPause() {

	//toggle paused
	if (!run) {
		if(esc->getLift()) run = true;
	}
	else {
		if (esc->getPress()) {
			togglePause();
			run = false;
		}
	}
}