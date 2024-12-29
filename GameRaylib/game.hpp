#pragma once
#include "spaceShip.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryShip.hpp"
#include "heart.hpp"

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();
	bool run;
	int lives;
	int score;
	int highScore;
	Music music;
private:
	void DeleteInactiveLasers();
	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> CreateAliens();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShootLaser();
	void CheckForCollision();
	void GameOver();
	void Reset();
	void InitGame();
	void CheckForHighScore();
	void saveHighScoreToFile(int highScore);
	int loadHighScoreFromFile();
	SpaceShip spaceship;
	MysteryShip mysteryShip;
	Heart spaceshipHeart;
	std::vector<Obstacle> obstacles;
	std::vector<Alien> aliens;
	int aliensDirecrion;
	std::vector<Laser> alienLasers;
	constexpr static float alienLaserShooterInterval = 0.35;
	float timeLastAlienFired;
	float mysteryShipSpawnInternal;
	float heartSpawnInternal;
	float timeLastSpawnMysteryShip;
	float timeLastSpawnHeart;
	Sound explosionSound;
};