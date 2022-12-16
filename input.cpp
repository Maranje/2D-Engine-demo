#include "input.h"

input::input(element* Owner, int ScanCode) : component(Owner) {
	keyState = nullptr;
	scanCode = ScanCode;
	wasPressed = false;
}

bool input::getPress() {
	keyState = SDL_GetKeyboardState(NULL);

	if (keyState[scanCode] && !wasPressed) {
		wasPressed = true; //set bool to true so the function only returns true once per press
		return true;		
	}
	return false;
}

bool input::getActivePress() {
	keyState = SDL_GetKeyboardState(NULL);

	if (keyState[scanCode]) {
		wasPressed = true; //set bool to true for use by subsequent lift function
		return true;
	}
	return false;
}

bool input::getLift() {
	keyState = SDL_GetKeyboardState(NULL);

	//has to run getPress() because keyState[] never returns false
	if (!getActivePress() && wasPressed) {
		wasPressed = false; //reset bool
		return true;
	}

	return false;
}