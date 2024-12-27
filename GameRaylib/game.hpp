#pragma once
#include "spaceShip.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryShip.hpp"

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
	std::vector<Alien> CreateAliens();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShootLaser();
	SpaceShip spaceship;
	MysteryShip mysteryShip;
	std::vector<Obstacle> obstacles;
	std::vector<Alien> aliens;
	int aliensDirecrion;
	std::vector<Laser> alienLasers;
	constexpr static float alienLaserShooterInterval = 0.35;
	float timeLastAlienFired;
	float mysteryShipSpawnInternal;
	float timeLastSpawn;
};