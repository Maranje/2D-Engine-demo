#include "interaction.h"

interaction::interaction(element* Owner) : component(Owner) {
	owner = Owner;
	screenWidth = Owner->getGame()->getScreenX();
	screenHeight = Owner->getGame()->getScreenY();
	center = owner->getPosition();
	interactionRect = new SDL_Rect;

	localRect = new SDL_Rect;
	localRect->x = center.x - (screenWidth / 2);
	localRect->y = center.y - (screenHeight / 2);
	localRect->w = screenWidth;
	localRect->h = screenHeight;

	scanWide = true;

	owner->getGame()->addInteraction(this);
}

interaction::~interaction() {
	owner->getGame()->removeInteraction(this);
}

void interaction::setInteractionArea(int width, int height, Vector2 OffCenterPosition) {
	offCenterPosition = OffCenterPosition;
	interactionRect->w = static_cast<int>(width * owner->getGame()->getScale());
	interactionRect->h = static_cast<int>(height * owner->getGame()->getScale());
	interactionRect->x = center.x - (interactionRect->w / 2) - static_cast<int>(offCenterPosition.x * owner->getGame()->getScale());
	interactionRect->y = center.y - (interactionRect->h / 2) - static_cast<int>(offCenterPosition.y * owner->getGame()->getScale());
}

void interaction::update(float deltaTime) {
	center = owner->getPosition();
	//update the position of the interaction rect
	interactionRect->x = center.x - (interactionRect->w / 2) - static_cast<int>(offCenterPosition.x * owner->getGame()->getScale());
	interactionRect->y = center.y - (interactionRect->h / 2) - static_cast<int>(offCenterPosition.y * owner->getGame()->getScale());
	//check to see if object is approaching the bounds of the local rect
	if ((center.x - interactionRect->w) <= localRect->x ||
		(center.x + interactionRect->w) >= (localRect->x + localRect->w) ||
		(center.y - interactionRect->h) <= localRect->y ||
		(center.y + interactionRect->h) >= (localRect->y + localRect->h)) {
		scanWide = true; //set to rescan local area
		localRect->x = center.x - (screenWidth / 2); //update local rect x-position
		localRect->y = center.y - (screenHeight / 2); //update local rect y-position
	}
}

void interaction::checkInteractionWide() {
	//removes self from scene list of all interaction objects
	owner->getGame()->removeInteraction(this);
	//clear list of local interactors
	localInteractions.clear();
	//iterates thru list of all interaction objects to determine which objects are close enough to be considered local
	for (auto rect : owner->getGame()->getInteractions()) {
		if (SDL_HasIntersection(localRect, rect->getInteractionRect())) {
			localInteractions.emplace_back(rect);//place interaction object in list of local colliders
		}
	}
	owner->getGame()->addInteraction(this);//replace self into list of all interaction objects
	scanWide = false; //set scanWide to false so that a full scene scan for interaction objects happens only when required
}

bool interaction::checkInteractionLocal() {
	for (auto rect : localInteractions) {
		if (SDL_HasIntersection(interactionRect, rect->getInteractionRect())) {
			return true;
		}
	}
	return false;
}

bool interaction::detectInteraction() {
	if (scanWide) checkInteractionWide();
	return checkInteractionLocal();
}