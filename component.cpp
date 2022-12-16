#include "component.h"

component::component(element* Owner, int UpdateOrder){
	owner = Owner;
	updateOrder = UpdateOrder;
	owner->addComponent(this); //add component to respective element's components vector
}

component::~component() {
	owner->removeComponent(this); //remove component from respective element's components vector
}

void component::update(float deltaTime){}