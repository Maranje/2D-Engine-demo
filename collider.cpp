#include "collider.h"

collider::collider(element* Owner) : component(Owner) {
	owner = Owner;
	screenWidth = Owner->getGame()->getScreenX();
	screenHeight = Owner->getGame()->getScreenY();
	center = owner->getPosition();
	collisionRect = new SDL_Rect;

	localRect = new SDL_Rect;
	localRect->x = center.x - (screenWidth / 2);
	localRect->y = center.y - (screenHeight / 2);
	localRect->w = screenWidth;
	localRect->h = screenHeight;

	scanWide = true;

	owner->getGame()->addCollider(this);
}

collider::~collider() {
	owner->getGame()->removeCollider(this);
}

void collider::setCollisionBody(int width, int height, Vector2 OffCenterPosition) {
	offCenterPosition = OffCenterPosition;
	collisionRect->x = center.x - (width / 2) - offCenterPosition.x;
	collisionRect->y = center.y - (height / 2) - offCenterPosition.y;
	collisionRect->w = width;
	collisionRect->h = height;
}

void collider::update(float deltaTime) {
	center = owner->getPosition();
	//update the position of the collision rect
	collisionRect->x = center.x - (collisionRect->w / 2) - offCenterPosition.x;
	collisionRect->y = center.y - (collisionRect->h / 2) - offCenterPosition.y;
	//check to see if object is approaching the bounds of the local rect
	if ((center.x - collisionRect->w) <= localRect->x || 
		(center.x + collisionRect->w) >= (localRect->x + localRect->w) || 
		(center.y - collisionRect->h) <= localRect->y || 
		(center.y + collisionRect->h) >= (localRect->y + localRect->h)) {
		scanWide = true; //set to rescan local area
		localRect->x = center.x - (screenWidth / 2); //update local rect x-position
		localRect->y = center.y - (screenHeight / 2); //update local rect y-position
	}
}

void collider::checkCollisionWide() {
	//removes self from scene list of all collision objects
	owner->getGame()->removeCollider(this);
	//clear list of local colliders
	localColliders.clear();
	//iterates thru list of all collision objects to determine which objects are close enough to be considered local
	for (auto rect : owner->getGame()->getColliders()) {
		if (SDL_HasIntersection(localRect, rect->getCollisionBodyRect())) {
			localColliders.emplace_back(rect);//place collision object in list of local colliders
		}
	}
	owner->getGame()->addCollider(this);//replace self into list of all collision objects
	scanWide = false; //set scanWide to false so that a full scene scan for collision objects happens only when required
}

bool collider::checkCollisionLocal() {
	for (auto rect : localColliders) {
		if (SDL_HasIntersection(collisionRect, rect->getCollisionBodyRect())) {
			return true;
		}
	}
	return false;
}

bool collider::detectCollision() {
	if (scanWide) checkCollisionWide();
	return checkCollisionLocal();
}