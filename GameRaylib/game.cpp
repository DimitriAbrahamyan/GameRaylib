#include "game.hpp"

Game::Game() {
	InitGame();
}

Game::~Game() {
	Alien::UnloadImages();
}

void Game::Draw() {
	spaceship.Draw();

	for (auto& laser : spaceship.lasers) {
		laser.Draw();
	}

	for (auto& obstacle : obstacles) {
		obstacle.Draw();
	}

	for (auto& alien : aliens) {
		alien.Draw();	
	}

	for (auto& laser : alienLasers) {
		laser.Draw();
	}

	mysteryShip.Draw();
}


void Game::Update() {
	if (run) {

		double currentTime = GetTime();
		if (currentTime - timeLastSpawn > mysteryShipSpawnInternal) {
			mysteryShip.Spawn();
			timeLastSpawn = GetTime();
			mysteryShipSpawnInternal = GetRandomValue(10, 20);
		}

		for (auto& laser : spaceship.lasers) {
			laser.Update();
		}

		MoveAliens();

		AlienShootLaser();

		for (auto& laser : alienLasers) {
			laser.Update();
		}

		DeleteInactiveLasers();

		mysteryShip.Update();

		CheckForCollision();
	}
	else {
		if (IsKeyDown(KEY_ENTER)) {
			Reset();
			InitGame();
		}
	}
}

void Game::HandleInput() {
	if (run)
	{
		if (IsKeyDown(KEY_LEFT)) {
			spaceship.MoveLeft();
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			spaceship.MoveRight();
		}
		else if (IsKeyDown(KEY_SPACE)) {
			spaceship.FireLaser();
		}
	}
}

void Game::DeleteInactiveLasers()
{
	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end(); ) {
		if (!it->active) {
			it = spaceship.lasers.erase(it);
		} else {
			++it;
		}
	}

	for (auto it = alienLasers.begin(); it != alienLasers.end(); ) {
		if (!it->active) {
			it = alienLasers.erase(it);
		}
		else {
			++it;
		}
	}
}

std::vector<Obstacle> Game::CreateObstacles() {
	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (static_cast<float>(4) * obstacleWidth)) / 5;

	for (int i = 0; i < 4; ++i) {
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX,float(GetScreenHeight() - 200)}));
	}

	return obstacles;
}

std::vector<Alien> Game::CreateAliens() {
	std::vector<Alien> aliens;
	for (int row = 0; row < 5; ++row) {
		for (int column = 0; column < 11; ++column) {
			int alienType;
			switch (row) {
			case 0:
					alienType = 3;
				break;
			case 2:
			case 3:
				alienType = 2;
				break;
			default:
				alienType = 1;
				break;
			}

			float x = 75 + column * 55;
			float y = 110 + row * 55;
			aliens.push_back(Alien(alienType, { x,y }));
		}
	}

	return aliens;
}

void Game::MoveAliens() {


	for (auto& alien : aliens) {
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
			aliensDirecrion = -1;
		}
		else if (alien.position.x < 25){
			aliensDirecrion = 1;
		}

		alien.Update(aliensDirecrion);
	}
}

void Game::MoveDownAliens(int distance) {
	for (auto& alien : aliens) {
		alien.position.y += distance;
	}
}

void Game::AlienShootLaser() {
	double currentTime = GetTime();
	if (currentTime - timeLastAlienFired >= alienLaserShooterInterval && !aliens.empty()) {

		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2,
			alien.position.y + alien.alienImages[alien.type - 1].height }, 6));

		timeLastAlienFired = GetTime();
	}
}

void Game::CheckForCollision() {
	// Spaceship Lasers
	for (auto& laser : spaceship.lasers) {
		auto it = aliens.begin();
		while (it != aliens.end()) {
			if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
				score += it->type * 100;
				it = aliens.erase(it);
				laser.active = false;
			} else {
				++it;
			}
		}

		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = obstacle.blocks.erase(it);
					laser.active = false;
				} else {
					++it;
				}
			}
		}

		if (CheckCollisionRecs(mysteryShip.getRect(),laser.getRect())) {
			mysteryShip.alive = false;
			laser.active = false;
			score += 500;
		}
	}

	// Alien Lasers

	for (auto& laser : alienLasers) {
		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}

		if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
			laser.active = false;
			--lives;
			if (!lives) {
				GameOver();
			}
		}
	}

	// Alien Collision with Obstacle 

	for (auto& alien : aliens) {
		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
					it = obstacle.blocks.erase(it);
				} else {
					++it;
				}
			}
		}

		if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
			GameOver();
		}
	}
}

void Game::GameOver() {
	run = false;
}

void Game::Reset() {
	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();
}

void Game::InitGame() {
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliensDirecrion = 1;
	timeLastAlienFired = 0.0f;
	timeLastSpawn = 0.0f;
	lives = 3;
	score = 0;
	run = true;
	mysteryShipSpawnInternal = GetRandomValue(10, 20);
}
