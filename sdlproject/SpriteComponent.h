#pragma once
#include "Components.h"
#include "SDL.h"
#include "textureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
	SpriteComponent(const char* path, bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0, 6, 80);
		Animation ride = Animation(1, 5, 80);

		animations.emplace("Idle", idle);
		animations.emplace("Ride", ride);

		Play("Idle");
		//frames = nFrames;
		//speed = mSpeed;
		setTex(path);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = textureManager::LoadTexture(path);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;

		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		textureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}
	
	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};