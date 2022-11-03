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
	Vector2 getScaledPosition() { return Vector2(static_cast<int>(position.x / eGame->getScale()), static_cast<int>(position.y / eGame->getScale())); }

	//sets the center point of element
	void setPosition(Vector2 pos);

	//changes the current x position
	void increaseHorizontalPosition(int x) { position.x += static_cast<int>(x * eGame->getDeltaTime() * eGame->getScale()); }
	//changes the current y position
	void increaseVerticalPosition(int y) { position.y -= static_cast<int>(y * eGame->getDeltaTime() * eGame->getScale()); }

	//returns current element state
	elementState getState() { return state; }
	//sets current element state
	void setState(elementState State) { state = State; }

	//returns pointer to game
	game* getGame() { return eGame; }

protected:
	game* eGame; //pointer to game
	elementState state; //current state of element

private:
	Vector2 position; //stores center point position of element
	std::vector<class component*> components; //vector for storing a list of all attached element components
	int order; //save the rendering order of the element
};
