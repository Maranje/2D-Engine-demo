#include "sprite.h"

sprite::sprite(element* Owner, SDL_Renderer* Renderer, int Width, int Height, int DrawOrder) : component(Owner, DrawOrder) {
	owner = Owner;
	renderer = Renderer;
	width = static_cast<int>(Width * owner->getGame()->getScale());
	height = static_cast<int>(Height * owner->getGame()->getScale());
	drawOrder = DrawOrder;

	texture = nullptr;
	source = nullptr;
	drawRect = new SDL_Rect;

	animated = false;

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
			if(cycles > 0) runs++; //increments the number of elapsed cycles by one
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
	if (texture) {
		drawRect->w = width;
		drawRect->h = height;
		drawRect->x = owner->getPosition().x - (width / 2) -owner->getGame()->getCamera()->x;
		drawRect->y = owner->getPosition().y - (height / 2) -owner->getGame()->getCamera()->y;
		SDL_RenderCopy(renderer, texture, source, drawRect);
	}
}

void sprite::setTexture(const char* Texture) {
	SDL_Surface* temp = IMG_Load(Texture);
	if (!temp) SDL_Log("ERROR LOADING IMAGE: %s", SDL_GetError());
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
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
}

void sprite::destroyTexture() {
	SDL_DestroyTexture(texture);
}