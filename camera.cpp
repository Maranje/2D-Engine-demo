#include "camera.h"

camera::camera(element* Owner) : component(Owner) {
	owner = Owner;
	x = owner->getPosition().x - (owner->getGame()->getCamera()->w / 2);
	y = owner->getPosition().y - (owner->getGame()->getCamera()->h / 2);
	owner->getGame()->setCamera(x, y);
	haltX = false;
	haltY = false;
}

void camera::update(float deltaTime) {
	//update camera position
	if (!haltX) {
		x = owner->getPosition().x - (owner->getGame()->getCamera()->w / 2);
	}
	if(!haltY){
		y = owner->getPosition().y - (owner->getGame()->getCamera()->h / 2);
		
	}
	owner->getGame()->setCamera(x, y);
}