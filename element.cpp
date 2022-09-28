#include "element.h"

element::element(game* game) {
	eGame = game;
	state = active;
	order = 0;
}

element::~element() {
	//eGame->removeComponent(this);
	while (!components.empty()) delete components.back();
}

void element::update(float deltaTime) {
	updateComponents(deltaTime);
	updateElement(deltaTime);
}

void element::updateComponents(float deltaTime) {
	if (state = active) {
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
	auto iteration = std::find(components.begin(), components.end(), component);
	if (iteration != components.end()) {
		components.erase(iteration);
	}
}