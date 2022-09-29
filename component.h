#pragma once
#include "element.h"

class component
{
public:
	component(class element* Owner, int UpdatOrder = 100);
	virtual ~component();
	virtual void update(float deltaTime);

	int getUpdateOrder() { return updateOrder; }
private:
	int updateOrder; //order in which components will be updated within the element
	class element* owner;
};
