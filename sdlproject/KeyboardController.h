#pragma once
#include "game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void update() override {
		if (game::event.type == SDL_KEYDOWN) {
			switch (game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("Ride");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Ride");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Ride");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Ride");
				break;
			default:
				break;
			}
		}

		if (game::event.type == SDL_KEYUP) {
			switch (game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				game::isRunning = false;
			default:
				break;
			}
		}
	}
};
