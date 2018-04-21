#include "map.h"
#include "game.h"
#include <fstream>

/*
int worldone[20][25] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,1,2,2,2,2,2,2 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,1,2,2,2,2,2,2 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,1,2,2,2,2,2,2 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};
*/

map::map() {
	/*
	dirt = textureManager::LoadTexture("assets/dirt.png");
	water = textureManager::LoadTexture("assets/water.png");
	grass = textureManager::LoadTexture("assets/grass.png");

	loadMap(worldone);

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;
	*/
}

map::~map() {
	/*
	SDL_DestroyTexture(dirt);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
	*/
}

void map::loadMap(std::string path, int sizeX, int sizeY) {
	/*
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			world[row][column] = arr[row][column];
		}
	}
	*/
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * 50;
			mapFile.get(c);
			srcX = atoi(&c) * 50;

			game::AddTile(srcX, srcY, x * 50, y * 50);
			mapFile.ignore();
		}
	}

	mapFile.close();
}
/*
void map::drawMap() {
	int type = 0;

	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			type = world[row][column];
			
			dest.x = column * 32;
			dest.y = row * 32;

			switch (type)
			{
			default:
				textureManager::Draw(water, src, dest);
				break;
			case 0:
				textureManager::Draw(water, src, dest);
				break;
			case 1:
				textureManager::Draw(dirt, src, dest);
				break;
			case 2:
				textureManager::Draw(grass, src, dest);
				break;
			}
		}
	}
}
*/