#include "game.h"

int main(int argc, char* argv[]) {

	game* Game;
	Game = new game();

	bool run = Game->init();
	if (run) {
		Game->runLoop();
	}

	delete Game;

	return 0;
}