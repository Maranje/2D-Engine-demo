#include "camera.h"

camera::camera(element* Owner) : component(Owner) {
	owner = Owner;
	x = owner->getPosition().x - (owner->getGame()->getCamera()->w / 2);
	y = owner->getPosition().y - (owner->getGame()->getCamera()->h / 2);
	owner->getGame()->setCamera(x, y);
}

void camera::update(float deltaTime) {
	//update camera position
	x = owner->getPosition().x - (owner->getGame()->getCamera()->w / 2);
	y = owner->getPosition().y - (owner->getGame()->getCamera()->h / 2);
	owner->getGame()->setCamera(x, y);
}