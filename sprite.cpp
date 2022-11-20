#include "sprite.h"

sprite::sprite(element* Owner, int Width, int Height, Vector2 Offset, int DrawOrder) : component(Owner, DrawOrder) {
	owner = Owner;
	renderer = owner->getGame()->getRenderer();
	width = static_cast<int>(Width * owner->getGame()->getScale());
	height = static_cast<int>(Height * owner->getGame()->getScale());
	drawOrder = DrawOrder;
	offset = Offset;

	texture0 = nullptr;
	texture1 = nullptr;
	texture2 = nullptr;
	texture3 = nullptr;
	texture4 = nullptr;
	texture5 = nullptr;
	texture6 = nullptr;
	texture7 = nullptr;
	texture8 = nullptr;
	source = nullptr;
	drawRect = new SDL_Rect;

	animated = false;
	cameraNeutral = false;

	sheetSize = Vector2(0, 0);
	cycleFrom = Vector2(0, 0);
	cycleUntil = Vector2(0, 0);
	frameCount_x = 0;
	frameCount_y = 0;
	cycles = 0;
	frame = 0.0f;
	fps = 0;
	runs = 0;

	owner->getGame()->addSprite(this);
}

sprite::~sprite() {
	destroyTexture();
	owner->getGame()->removeSprite(this);
}

void sprite::update(float deltaTime) {
	//sprite animation if animate has been set to true
	if (animated) {
		//frame increases as a function of delta time
		frame += fps * deltaTime;
		//this condition catches the animation frame when it reaches cycleUntil and sends it back to cycleFrom
		if (source->y >= (cycleUntil.y * (sheetSize.y / frameCount_y)) 
			&& source->x == (cycleUntil.x * (sheetSize.x / frameCount_x))
			&& frame >= static_cast<float>(sheetSize.x) / frameCount_x) {
			runs++; //increments the number of elapsed cycles by one
			if (runs == cycles) animated = false; //this ends the animation if the number of cycles desired is reached
			source->x = cycleFrom.x * (sheetSize.x / frameCount_x);
			source->y = cycleFrom.y * (sheetSize.y / frameCount_y);
			frame = 0.0f;
		}
		//this checks for when the value of frame has reached the point at which the animation frame should 
		//shift horizontally by one frame
		if (frame >= static_cast<float>(sheetSize.x) / frameCount_x) {
			source->x += sheetSize.x / frameCount_x;
			frame = 0.0f;
		}
		//this checks for when the animation frame has reached the horizontal limit, sends it back to the
		//horizontal origin, and shift the frame vertically down by one
		if (source->x >= sheetSize.x) {
			source->x = 0;
			source->y += sheetSize.y / frameCount_y;
		}
	}
}

void sprite::draw() {
	if (texture0) {
		drawRect->w = width;
		drawRect->h = height;
		if (cameraNeutral) {
			drawRect->x = static_cast<int>(owner->getPosition().x - (width / 2) + (offset.x * owner->getGame()->getScale()));
			drawRect->y = static_cast<int>(owner->getPosition().y - (height / 2) - (offset.y * owner->getGame()->getScale()));
		}
		else {
			drawRect->x = static_cast<int>(owner->getPosition().x - (width / 2) - owner->getGame()->getCamera()->x + (offset.x * owner->getGame()->getScale()));
			drawRect->y = static_cast<int>(owner->getPosition().y - (height / 2) - owner->getGame()->getCamera()->y - (offset.y * owner->getGame()->getScale()));
		}
		SDL_RenderCopy(renderer, texture0, source, drawRect);
		//fucking atrocious. yuck.
		if (texture1) SDL_RenderCopy(renderer, texture1, source, drawRect);
		if (texture2) SDL_RenderCopy(renderer, texture2, source, drawRect);
		if (texture3) SDL_RenderCopy(renderer, texture3, source, drawRect);
		if (texture4) SDL_RenderCopy(renderer, texture4, source, drawRect);
		if (texture5) SDL_RenderCopy(renderer, texture5, source, drawRect);
		if (texture6) SDL_RenderCopy(renderer, texture6, source, drawRect);
		if (texture7) SDL_RenderCopy(renderer, texture7, source, drawRect);
		if (texture8) SDL_RenderCopy(renderer, texture8, source, drawRect);
	}
}

void sprite::setDrawOrderByVerticalPosition(int Offset){
	drawOrder = owner->getPosition().y - static_cast<int>(Offset * owner->getGame()->getScale());
}

void sprite::setDrawOrderByHorizontalPosition(int Offset){
	drawOrder = owner->getPosition().x - static_cast<int>(Offset * owner->getGame()->getScale());
}

void sprite::setTexture(const char* Texture) {
	SDL_Surface* temp = IMG_Load(Texture);
	if (!temp) SDL_Log("ERROR LOADING IMAGE: %s", SDL_GetError());
	texture0 = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
}

/// <summary>
/// adds up to 7 layerst to an existing sprite texture
/// </summary>
/// <param name="Texture: filepath of the image to be added"></param>
/// <param name="layer: int ranging from 1-8 for indicating layer level. 1 = bottom-most, 8 = top"></param>
void sprite::updateTexture(const char* Texture, int layer) {
	SDL_Surface* temp = IMG_Load(Texture);
	if (!temp) SDL_Log("ERROR LOADING IMAGE: %s", SDL_GetError());
	switch (layer) {
	case 1: 
		texture1 = SDL_CreateTextureFromSurface(renderer, temp);
		break;
	case 2:
		texture2 = SDL_CreateTextureFromSurface(renderer, temp);
		break;
	case 3:
		texture3 = SDL_CreateTextureFromSurface(renderer, temp);
		break;
	case 4:
		texture4 = SDL_CreateTextureFromSurface(renderer, temp);
		break;
	case 5:
		texture5 = SDL_CreateTextureFromSurface(renderer, temp);
		break;
	case 6:
		texture6 = SDL_CreateTextureFromSurface(renderer, temp);
		break;
	case 7:
		texture7 = SDL_CreateTextureFromSurface(renderer, temp);
		break;
	case 8:
		texture8 = SDL_CreateTextureFromSurface(renderer, temp);
		break;
	}
	SDL_FreeSurface(temp);
}

void sprite::updateDrawOrder(){
	owner->getGame()->removeSprite(this);
	owner->getGame()->addSprite(this);
}

void sprite::setSource(int X, int Y, int W, int H) {
	source = new SDL_Rect;
	source->x = X;
	source->y = Y;
	source->w = W;
	source->h = H;
}

void sprite::setAnimated(bool Animated, 
						 Vector2 SheetSize, 
						 int FrameCount_x, 
						 int FrameCount_y, 
						 int FPS, 
						 Vector2 beginAt,
						 Vector2 CycleFrom, 
						 Vector2 CycleUntil, 
						 int numberOfCycles){
	animated = Animated;
	sheetSize = SheetSize;
	frameCount_x = FrameCount_x;
	frameCount_y = FrameCount_y;
	fps = FPS;
	cycleFrom = CycleFrom;
	cycleUntil = CycleUntil;
	cycles = numberOfCycles;
	source->x = beginAt.x * (sheetSize.x / frameCount_x);
	source->y = beginAt.y * (sheetSize.y / frameCount_y);
	runs = 0;
}

void sprite::destroyTexture() {
	SDL_DestroyTexture(texture0);
	//just awful
	if (texture1) SDL_DestroyTexture(texture1);
	if (texture2) SDL_DestroyTexture(texture2);
	if (texture3) SDL_DestroyTexture(texture3);
	if (texture4) SDL_DestroyTexture(texture4);
	if (texture5) SDL_DestroyTexture(texture5);
	if (texture6) SDL_DestroyTexture(texture6);
	if (texture7) SDL_DestroyTexture(texture7);
	if (texture8) SDL_DestroyTexture(texture8);
}