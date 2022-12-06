#include "pizzaPause.h"
#include "element.h"
#include "sprite.h"
#include "input.h"
#include "camera.h"

pizzaPause::pizzaPause(class game* Game, class element* Owner, class input* ESC) : pause(Game){
	owner = Owner;
	enter = new input(owner, SDL_SCANCODE_RETURN);
	up = new input(owner, SDL_SCANCODE_UP);
	down = new input(owner, SDL_SCANCODE_DOWN);
	esc = ESC;
	run = false;
	animate = false;
	selection = 0;
	menuScreen = nullptr;
}

pizzaPause::~pizzaPause() {
}

void pizzaPause::runPause() {
	//toggle paused
	if (!run) {
		if (esc->getLift()) {
			run = true;
			menuScreen = new sprite(owner, 480, 270, Vector2(0, 0), 9999999);
			menuScreen->setTexture("assets/art/Pause_menu.png");
			menuScreen->setSource(0, 0, 480, 270);
			menuScreen->setCentered(true);
		}
	}
	else {
		menuScreen->update(pGame->getDeltaTime()); //update menu sprite since the update function in game is halted
		if (esc->getPress()) {
			togglePause();
			delete menuScreen;
			run = false;
			selection = 0;
		}
		if (!menuScreen->getAnimated()) {
			switch (selection) {
			case 0:
				if (up->getPress()) {
					selection = 4;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 5),
						Vector2(0, 6),
						Vector2(0, 6),
						1
					);
				}
				else if (down->getPress()) {
					selection = 1;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 0),
						Vector2(0, 1),
						Vector2(0, 1),
						1
					);
				}
				break;
			case 1:
				if (up->getPress()) {
					selection = 0;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 9),
						Vector2(0, 0),
						Vector2(7, 9),
						1
					);
				}
				else if (down->getPress()) {
					selection = 2;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 1),
						Vector2(0, 2),
						Vector2(0, 2),
						1
					);
				}
				break;
			case 2:
				if (up->getPress()) {
					selection = 1;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 8),
						Vector2(0, 9),
						Vector2(0, 9),
						1
					);
				}
				else if (down->getPress()) {
					selection = 3;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 2),
						Vector2(0, 3),
						Vector2(0, 3),
						1
					);
				}
				break;
			case 3:
				if (up->getPress()) {
					selection = 2;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 7),
						Vector2(0, 8),
						Vector2(0, 8),
						1
					);
				}
				else if (down->getPress()) {
					selection = 4;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 3),
						Vector2(0, 4),
						Vector2(0, 4),
						1
					);
				}
				break;
			case 4:
				if (up->getPress()) {
					selection = 3;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 6),
						Vector2(0, 7),
						Vector2(0, 7),
						1
					);
				}
				else if (down->getPress()) {
					selection = 0;
					menuScreen->setAnimated(
						true,
						Vector2(3840, 2700),
						8, 10,
						18000,
						Vector2(0, 4),
						Vector2(0, 5),
						Vector2(0, 5),
						1
					);
				}
				break;
			}
			up->getLift();
			down->getLift();
		}
	}
}