#pragma once
#include "element.h"

class component
{
public:
	component(class element* Owner, int UpdatOrder = 100);
	virtual ~component();
	virtual void update(float deltaTime);

	//returns order in which a component is added to its respective element components vector
	int getUpdateOrder() { return updateOrder; }
private:
	int updateOrder; //order in which components will be updated within the element
	class element* owner;
};
