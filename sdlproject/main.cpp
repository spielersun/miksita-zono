#include "game.h"
#include <iostream>

using namespace std;

/*
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	return 0;
}
*/

game *gameinstance = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	gameinstance = new game();
	gameinstance->init("farplanets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1250, 1000, false);

	while (gameinstance->running()) {
		frameStart = SDL_GetTicks();

		gameinstance->handleEvents();
		gameinstance->update();
		gameinstance->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }
	}

	gameinstance->clean();
	return 0;
}