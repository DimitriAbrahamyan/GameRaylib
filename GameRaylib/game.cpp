#include "game.hpp"
#include <fstream>
#include <iostream>

// Constructor to initialize the game
Game::Game() {
	// Load music and sound effects
	music = LoadMusicStream("Sounds/music.ogg");
	explosionSound = LoadSound("Sounds/explosion.ogg");

	// Start playing the background music
	PlayMusicStream(music);

	// Initialize the game elements
	InitGame();
}

// Destructor to clean up resources when the game ends
Game::~Game() {
	// Unload images used by the Alien class (presumably alien sprites or textures)
	Alien::UnloadImages();

	// Unload music and sound effects
	UnloadMusicStream(music);
	UnloadSound(explosionSound);
}

// Function to draw all game objects to the screen
void Game::Draw() {
	// Draw the spaceship
	spaceship.Draw();

	// Draw all the lasers fired by the spaceship
	for (auto& laser : spaceship.lasers) {
		laser.Draw();
	}

	// Draw all obstacles in the game
	for (auto& obstacle : obstacles) {
		obstacle.Draw();
	}

	// Draw all aliens
	for (auto& alien : aliens) {
		alien.Draw();
	}

	// Draw all lasers fired by the aliens
	for (auto& laser : alienLasers) {
		laser.Draw();
	}

	// Draw the mystery ship
	mysteryShip.Draw();

	// Draw the spaceship heart (could be an extra life or a special object)
	spaceshipHeart.Draw();
}

// Function to update the game state every frame
void Game::Update() {
	if (run) {
		// Get the current game time
		double currentTime = GetTime();

		// Spawn the mystery ship at random intervals
		if (currentTime - timeLastSpawnMysteryShip > mysteryShipSpawnInternal) {
			mysteryShip.Spawn();
			timeLastSpawnMysteryShip = GetTime(); // Update the last spawn time
			mysteryShipSpawnInternal = GetRandomValue(10, 20); // Randomize the next spawn interval
		}

		// Spawn the spaceship heart at random intervals
		if (currentTime - timeLastSpawnHeart > heartSpawnInternal) {
			spaceshipHeart.Spawn();
			timeLastSpawnHeart = GetTime(); // Update the last spawn time
			heartSpawnInternal = GetRandomValue(10, 20); // Randomize the next spawn interval
		}

		// Update all lasers fired by the spaceship
		for (auto& laser : spaceship.lasers) {
			laser.Update();
		}

		// Move the aliens on the screen
		MoveAliens();

		// Make the aliens shoot lasers at the player
		AlienShootLaser();

		// Update all lasers fired by the aliens
		for (auto& laser : alienLasers) {
			laser.Update();
		}

		// Delete lasers that are no longer active (e.g., they went off-screen or collided)
		DeleteInactiveLasers();

		// Update the mystery ship and spaceship heart
		mysteryShip.Update();
		spaceshipHeart.Update();

		// Check for collisions between various game objects
		CheckForCollision();
	}
	else {
		// If the game is not running, listen for the ENTER key to restart the game
		if (IsKeyDown(KEY_ENTER)) {
			Reset(); // Reset the game state
			InitGame(); // Reinitialize the game
		}
	}
}

void Game::HandleInput() {
    if (run) {
        // Check for left movement input and move spaceship left
        if (IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        }
        // Check for right movement input and move spaceship right
        else if (IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        }
        // Check for spacebar input and fire laser from spaceship
        else if (IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser();
        }
    }
}

void Game::DeleteInactiveLasers() {
    // Remove inactive spaceship lasers
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end(); ) {
        if (!it->active) {
            it = spaceship.lasers.erase(it); // Remove laser if inactive
        }
        else {
            ++it;
        }
    }

    // Remove inactive alien lasers
    for (auto it = alienLasers.begin(); it != alienLasers.end(); ) {
        if (!it->active) {
            it = alienLasers.erase(it); // Remove laser if inactive
        }
        else {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles() {
    // Calculate obstacle width and gap for positioning
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (static_cast<float>(4) * obstacleWidth)) / 5;

    // Create 4 obstacles positioned on the screen
    for (int i = 0; i < 4; ++i) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 200) }));
    }

    return obstacles; // Return the created obstacles
}

std::vector<Alien> Game::CreateAliens() {
    std::vector<Alien> aliens;
    // Create a grid of aliens with different types based on their row
    for (int row = 0; row < 5; ++row) {
        for (int column = 0; column < 11; ++column) {
            int alienType;
            switch (row) {
            case 0:
                alienType = 3; // Strongest aliens on the top row
                break;
            case 2:
            case 3:
                alienType = 2; // Mid-tier aliens
                break;
            default:
                alienType = 1; // Weakest aliens on the bottom rows
                break;
            }

            // Calculate position for each alien
            float x = 75 + column * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, { x, y }));
        }
    }

    return aliens; // Return the created aliens
}

void Game::MoveAliens() {
    // Move all aliens, checking boundaries and moving them down if necessary
    for (auto& alien : aliens) {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            aliensDirecrion = -1; // Change direction to left
            MoveDownAliens(4); // Move down the aliens
        }
        else if (alien.position.x < 25) {
            aliensDirecrion = 1; // Change direction to right
            MoveDownAliens(4); // Move down the aliens
        }

        alien.Update(aliensDirecrion); // Update alien movement
    }
}

void Game::MoveDownAliens(int distance) {
    // Move all aliens down by the specified distance
    for (auto& alien : aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser() {
    // Check if the time to shoot has passed and if aliens are available
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShooterInterval && !aliens.empty()) {

        // Choose a random alien to shoot a laser
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2,
                                      alien.position.y + alien.alienImages[alien.type - 1].height }, 6));

        timeLastAlienFired = GetTime(); // Update last fired time
    }
}

void Game::CheckForCollision() {
    // Check collisions for spaceship lasers
    for (auto& laser : spaceship.lasers) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            // Check for collision between spaceship laser and alien
            if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                PlaySound(explosionSound); // Play explosion sound
                score += it->type * 100; // Increase score based on alien type

                CheckForHighScore(); // Check if it's a new high score
                it = aliens.erase(it); // Remove the alien
                laser.active = false; // Deactivate laser
            }
            else {
                ++it;
            }
        }

        // Check for collisions with obstacles
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it); // Remove the block from obstacle
                    laser.active = false; // Deactivate laser
                }
                else {
                    ++it;
                }
            }
        }

        // Check for collision with mystery ship
        if (CheckCollisionRecs(mysteryShip.getRect(), laser.getRect())) {
            mysteryShip.alive = false; // Destroy mystery ship
            laser.active = false; // Deactivate laser
            score += 500; // Reward player with points
            CheckForHighScore(); // Check if it's a new high score
            PlaySound(explosionSound); // Play explosion sound
        }
    }

    // Check collisions for alien lasers
    for (auto& laser : alienLasers) {
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it); // Remove block if hit by laser
                    laser.active = false; // Deactivate laser
                }
                else {
                    ++it;
                }
            }
        }

        // Check if alien laser hits the spaceship
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false; // Deactivate laser
            --lives; // Decrease lives
            if (!lives) {
                GameOver(); // End game if no lives left
            }
        }

        // Check for collision with spaceship heart (extra life)
        if (CheckCollisionRecs(spaceshipHeart.getRect(), spaceship.getRect())) {
            spaceshipHeart.active = false; // Remove heart
            ++lives; // Increase lives
            if (lives > 3) {
                lives = 3; // Cap lives to 3
            }
        }
    }

    // Check collisions for aliens with obstacles
    for (auto& alien : aliens) {
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it); // Remove block if alien hits it
                }
                else {
                    ++it;
                }
            }
        }

        // Check if alien collides with spaceship
        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver(); // End game if alien hits spaceship
        }
    }
}

void Game::GameOver() {
    run = false; // Stop the game
}

void Game::Reset() {
    spaceship.Reset(); // Reset spaceship
    aliens.clear(); // Clear all aliens
    alienLasers.clear(); // Clear all alien lasers
    obstacles.clear(); // Clear all obstacles
}

void Game::InitGame() {
    // Initialize game objects like obstacles, aliens, and variables
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirecrion = 1; // Initial direction of aliens
    timeLastAlienFired = 0.0f; // Time since last alien fired
    timeLastSpawnMysteryShip = 0.0f; // Time since last mystery ship spawned
    timeLastSpawnHeart = 0.0f; // Time since last heart spawned
    lives = 3; // Start with 3 lives
    score = 0; // Start with 0 score
    highScore = loadHighScoreFromFile(); // Load high score from file
    run = true; // Start the game
    mysteryShipSpawnInternal = GetRandomValue(10, 20); // Randomize mystery ship spawn interval
    heartSpawnInternal = GetRandomValue(10, 20); // Randomize heart spawn interval
}

void Game::CheckForHighScore() {
    // Check if the current score is higher than the high score and update if needed
    if (score > highScore) {
        highScore = score; // Update high score
        saveHighScoreToFile(highScore); // Save the new high score to file
    }
}

void Game::saveHighScoreToFile(int highScore) {
    // Save the high score to a file
    std::ofstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile << highScore;
        highscoreFile.close();
    }
    else {
        std::cerr << "Failed to save highscore to file\n"; // Error if file can't be opened
    }
}

int Game::loadHighScoreFromFile() {
    // Load the high score from a file
    int loadingHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile >> loadingHighscore;
        highscoreFile.close();
    }
    else {
        std::cerr << "Failed to load highscore from file\n"; // Error if file can't be opened
    }

    return loadingHighscore; // Return the loaded high score
}

