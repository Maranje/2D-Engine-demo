#include "element.h"
#include "component.h"

element::element(game* Game) {
	eGame = Game;
	state = active;
	order = 0;
	eGame->addElement(this);
	position = Vector2(eGame->getScreenX() / 2, eGame->getScreenY() / 2);
}

element::~element() {
	eGame->removeElement(this);
	while (!components.empty()) delete components.back();
}

void element::update(float deltaTime) {
	updateComponents(deltaTime);
	updateElement(deltaTime);
}

void element::updateComponents(float deltaTime) {
	if (state == active) {
		for (auto component : components) {
			component->update(deltaTime);
		}
	}
}

void element::updateElement(float deltaTime){}

void element::addComponent(component* Component) {
	order = Component->getUpdateOrder();
	auto iterate = components.begin();
	for (; iterate != components.end(); iterate++) {
		if (order < (*iterate)->getUpdateOrder()) break;
	}
	components.insert(iterate, Component);
}

void element::removeComponent(component* component) {
	auto item = std::find(components.begin(), components.end(), component);
	if (item != components.end()) { 
		components.erase(item);
	}
}

void element::setPosition(Vector2 pos) {
	position.x = (eGame->getScreenX() / 2) + pos.x;
	position.y = (eGame->getScreenY() / 2) - pos.y;
}