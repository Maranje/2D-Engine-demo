#include "input.h"

input::input(element* Owner, int ScanCode) : component(Owner) {
	keyState = nullptr;
	scanCode = ScanCode;
	isPressed = false;
	wasPressed = false;
}

bool input::getPress() {
	keyState = SDL_GetKeyboardState(NULL);

	if (keyState[scanCode] && !wasPressed) {
		wasPressed = true;
		return true;		
	}
	return false;
}

bool input::getActivePress() {
	keyState = SDL_GetKeyboardState(NULL);

	if (keyState[scanCode]) {
		wasPressed = true;
		return true;
	}
	return false;
}

bool input::getLift() {
	keyState = SDL_GetKeyboardState(NULL);

	//has to run getPress() because keyState[] never returns false
	if (!getActivePress() && wasPressed) {
		wasPressed = false;
		return true;
	}

	return false;
}