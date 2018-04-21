#pragma once
#include <string>

class map {
public:
	map();
	~map();

	static void loadMap(std::string path, int sizeX, int sizeY);
	//void drawMap();
private:
	/*
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int world[20][25];
	*/
};
