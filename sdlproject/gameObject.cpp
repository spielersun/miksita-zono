#include "gameObject.h"
#include "textureManager.h"

gameObject::gameObject(const char* texturesheet, int x, int y) {
	objTexture = textureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

void gameObject::Update() {
	xpos++;
	ypos++;

	srcRect.h = 95;
	srcRect.w = 150;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
	destRect.x = xpos;
	destRect.y = ypos;
}

void gameObject::Render() {
	SDL_RenderCopy(game::renderer, objTexture, &srcRect, &destRect);
}