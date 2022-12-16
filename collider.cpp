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
	offCenterPosition = OffCenterPosition; //moves collider rect along the element's own coordinates
	collisionRect->w = static_cast<int>(width * owner->getGame()->getScale()); //set width
	collisionRect->h = static_cast<int>(height * owner->getGame()->getScale()); //set height
	collisionRect->x = center.x - (collisionRect->w / 2) + static_cast<int>(offCenterPosition.x * owner->getGame()->getScale()); //set the center along the x-axis
	collisionRect->y = center.y - (collisionRect->h / 2) - static_cast<int>(offCenterPosition.y * owner->getGame()->getScale()); //set the center along the y-axis
	// the y-axis is inverted from the standard in which y values descend as they increase, to the traditional ascending y as values increase
}

void collider::update(float deltaTime) {
	center = owner->getPosition();
	//update the position of the collision rect
	collisionRect->x = center.x - (collisionRect->w / 2) + static_cast<int>(offCenterPosition.x * owner->getGame()->getScale());
	collisionRect->y = center.y - (collisionRect->h / 2) - static_cast<int>(offCenterPosition.y * owner->getGame()->getScale());
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
	//iterate through all collision objects in localColliders
	for (auto rect : localColliders) {
		//detect collisions between collider rects
		if (SDL_HasIntersection(collisionRect, rect->getCollisionBodyRect())) {
			return true; //return true if collision detected
		}
	}
	return false;
}

bool collider::detectCollision() {
	if (scanWide) checkCollisionWide();
	return checkCollisionLocal();
}