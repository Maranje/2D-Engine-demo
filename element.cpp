#include "element.h"
#include "component.h"

element::element(game* Game) {
	eGame = Game;
	state = active;
	renderer = eGame->getRenderer();
	order = 0;
	eGame->addElement(this);
	position = Vector2(eGame->getScreenX() / 2, eGame->getScreenY() / 2);
}

element::~element() {
	eGame->removeElement(this);
	while (!components.empty()) delete components.back();
}

void element::update(float deltaTime) {
	updateComponents(deltaTime); //update all proprietary components in the components vector
	updateElement(deltaTime); //virtual function for inherited elements to run their own update loop
}

void element::updateComponents(float deltaTime) {
	if (state == active) {
		for (auto component : components) {
			component->update(deltaTime); //update components in order
		}
	}
}

void element::updateElement(float deltaTime){}

void element::addComponent(component* Component) {
	order = Component->getUpdateOrder(); //store the order in which the component is to be placed within the components vector
	auto iterate = components.begin();
	for (; iterate != components.end(); iterate++) {
		if (order < (*iterate)->getUpdateOrder()) break; //find proper component position
	}
	components.insert(iterate, Component); //add component
}

void element::removeComponent(component* component) {
	auto item = std::find(components.begin(), components.end(), component);
	if (item != components.end()) { 
		components.erase(item); //remove component
	}
}

void element::setPosition(Vector2 pos) {
	position.x = (eGame->getScreenX() / 2) + static_cast<int>(pos.x * eGame->getScale()); //set x position
	position.y = (eGame->getScreenY() / 2) - static_cast<int>(pos.y * eGame->getScale()); //set y position
}