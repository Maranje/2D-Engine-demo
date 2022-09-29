#pragma once
#include "game.h"

class element
{
public:
	enum elementState {
		active,
		inactive,
		paused
	};

	element(game* Game);
	~element();

	//runs other update functions
	void update(float deltaTime);
	//updates all components attached to active element
	void updateComponents(float deltaTime);
	//used by inheritors
	virtual void updateElement(float deltaTime);

	void addComponent(class component* component);
	void removeComponent(class component* component);

	//returns the center point of element
	Vector2 getPosition() { return position; }
	//sets the center point of element
	void setPosition(Vector2 pos) { position = pos; }
	//returns current element state
	elementState getState() { return state; }
	//sets current element state
	void setState(elementState State) { state = State; }

	//returns pointer to game
	game* getGame() { return eGame; }

private:
	game* eGame; //pointer to game
	Vector2 position; //stores center point position of element
	elementState state; //current state of element
	std::vector<class component*> components; //vector for storing a list of all attached element components
	int order; //save the rendering order of the element
};

