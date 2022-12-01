#include "pause.h"
#include "game.h"

pause::pause(game* Game) {
	pGame = Game;
	pGame->createPause(this);
}

pause::~pause() {
	pGame->destroyPause();
}

void pause::togglePause() {
	pGame->togglePaused();
}

void pause::runPause() {

}