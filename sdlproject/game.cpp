#include "game.h"
#include "textureManager.h"
#include "map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

map* world;
Manager manager;

SDL_Renderer* game::renderer = nullptr;
SDL_Event game::event;

SDL_Rect game::camera = { 0,0,1250,1000 };

std::vector<ColliderComponent*> game::colliders;

bool game::isRunning = false;

auto& ship(manager.addEntity());
auto& floorTiles(manager.addEntity());

const char* mapfile = "assets/cslatemini.png";

enum groupLabels : std::size_t {
	groupMap,
	groupShips,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& ships(manager.getGroup(groupShips));
auto& enemies(manager.getGroup(groupEnemies));

/*
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());
*/

game::game()
{
}

game::~game()
{
}

void game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){ 
		std::cout << "Subsystems initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) { std::cout << "Window Created" << std::endl; }

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) { 
			SDL_SetRenderDrawColor(renderer, 233, 228, 219, 255);
			std::cout << "Renderer Created" << std::endl; 
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	world = new map();

	/*
	tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
	tile1.addComponent<ColliderComponent>("dirt");
	tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
	tile2.addComponent<ColliderComponent>("grass");
	*/

	map::loadMap("assets/mapnew.map", 25, 20);

	ship.addComponent<TransformComponent>();
	ship.addComponent<SpriteComponent>("assets/cartoffel_anims.png", true);
	ship.addComponent<KeyboardController>();
	ship.addComponent<ColliderComponent>("ship");
	ship.addGroup(groupShips);

	/*
	floorTiles.addComponent<TransformComponent>(0.0f, 320.0f, 32, 400, 1);
	floorTiles.addComponent<SpriteComponent>("assets/dirt.png");
	floorTiles.addComponent<ColliderComponent>("floorTiles");
	floorTiles.addGroup(groupMap);
	*/
}

void game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void game::update() {
	manager.refresh();
	manager.update();
	/*
	world->loadMap();
	std::cout << newShip.getComponent<PositionComponent>().x() << ", " << newShip.getComponent<PositionComponent>().y() << std::endl;
	ship.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
	if (ship.getComponent<TransformComponent>().position.x > 100) {
		ship.getComponent<SpriteComponent>().setTex("assets/badShip.png");
	}
	*/
	/*
	for(auto cc : colliders){
		Collision::AABB(ship.getComponent<ColliderComponent>(), *cc);
	}
	*/
	/*
	Vector2D pVel = ship.getComponent<TransformComponent>().velocity;
	int pSpeed = ship.getComponent<TransformComponent>().speed;

	for (auto t : tiles) {
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}
	*/

	camera.x = ship.getComponent<TransformComponent>().position.x - 625;
	camera.y = ship.getComponent<TransformComponent>().position.y - 500;

	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.y = camera.h;
	}
}

void game::render() {
	SDL_RenderClear(renderer);
	//world->drawMap();
	//cartoffel->Render();
	//manager.draw();
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& s : ships) {
		s->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

void game::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
	tile.addGroup(groupMap);
}