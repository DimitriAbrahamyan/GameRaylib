#pragma once
#include "spaceShip.hpp"
#include "obstacle.hpp"

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();

private:
	void DeleteInactiveLasers();
	std::vector<Obstacle> CreateObstacles();
	SpaceShip spaceship;
	std::vector<Obstacle> obstacles;
};