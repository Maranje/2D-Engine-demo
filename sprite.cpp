#include "sprite.h"

sprite::sprite(element* Owner, SDL_Renderer* Renderer, int Width, int Height, int DrawOrder) : component(Owner, DrawOrder) {
	owner = Owner;
	renderer = Renderer;
	width = Width;
	height = Height;
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
	frame = 0;
	fps = 0;
	runs = 0;

	owner->getGame()->addSprite(this);
}

sprite::~sprite() {
	owner->getGame()->removeSprite(this);
}

void sprite::update(float deltaTime) {

}

void sprite::draw() {
	if (texture) {
		drawRect->w = width;
		drawRect->h = height;
		drawRect->x = owner->getPosition().x - (width / 2) - owner->getGame()->getCamera()->x;
		drawRect->y = owner->getPosition().y - (height / 2) - owner->getGame()->getCamera()->y;
		SDL_RenderCopy(renderer, texture, source, drawRect);
	}
}

void sprite::setTexture(const char* Texture) {
	SDL_Surface* temp = IMG_Load(Texture);
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
}

void sprite::destroyTexture() {
	SDL_DestroyTexture(texture);
}