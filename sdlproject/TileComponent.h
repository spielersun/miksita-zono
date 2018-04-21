#pragma once
#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component {
public:
	/*
	TransformComponent *transform;
	SpriteComponent *sprite;

	SDL_Rect tileRect;
	int tileID;
	char* path;
	*/

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path){

		texture = textureManager::LoadTexture(path);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 50;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 50;

		/*
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "assets/water.png";
			break;
		case 1: 
			path = "assets/dirt.png";
			break;
		case 2:
			path = "assets/grass.png";
			break;
		default:	
			break;
		}
		*/
	}

	void update() override {
		destRect.x = position.x - game::camera.x;
		destRect.y = position.y - game::camera.y;
	}

	void draw() override {
		textureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
	/*
	void init() override {
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
	*/
};


