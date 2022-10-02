#include "input.h"

input::input(element* Owner, int ScanCode) : component(Owner) {
	keyState = nullptr;
	scanCode = ScanCode;
	wasPressed = false;
}

bool input::getPress() {
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
	//also, running getPress() would be required to set the value of wasPressed 
	//if you're exclusively checking for key lift
	if (!getPress() && wasPressed) {
		wasPressed = false;
		return true;
	}

	return false;
}