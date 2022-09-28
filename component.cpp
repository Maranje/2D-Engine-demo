#include "component.h"

component::component(element* Owner, int UpdateOrder){
	owner = Owner;
	updateOrder = UpdateOrder;
	owner->addComponent(this);
}

component::~component() {
	owner->removeComponent(this);
}

void component::update(float deltaTime){}