#pragma once
#include "spaceShip.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryShip.hpp"
#include "heart.hpp"

// The Game class manages the main game logic, including drawing, updating, 
// handling input, and managing game entities like spaceships, aliens, and obstacles.
class Game {
public:
    // Constructor: Initializes the game state and entities.
    Game();

    // Destructor: Cleans up any allocated resources.
    ~Game();

    // Draws all game entities and the game UI.
    void Draw();

    // Updates the game state, including moving entities and checking for collisions.
    void Update();

    // Handles user input, such as controlling the spaceship.
    void HandleInput();

    // Public variables:
    // 'run' determines if the game loop should continue running.
    bool run;

    // 'lives' represents the number of lives the player has left.
    int lives;

    // 'score' holds the player's current score.
    int score;

    // 'highScore' stores the highest score achieved.
    int highScore;

    // Background music for the game.
    Music music;

private:
    // Deletes lasers that are inactive or off-screen.
    void DeleteInactiveLasers();

    // Creates and returns a collection of obstacles for the game.
    std::vector<Obstacle> CreateObstacles();

    // Creates and returns a collection of aliens for the game.
    std::vector<Alien> CreateAliens();

    // Moves all aliens horizontally based on their direction.
    void MoveAliens();

    // Moves all aliens downward by the specified distance.
    void MoveDownAliens(int distance);

    // Allows an alien to shoot a laser at regular intervals.
    void AlienShootLaser();

    // Checks for collisions between various game entities (e.g., lasers, aliens, and the spaceship).
    void CheckForCollision();

    // Ends the game, displaying the game-over screen and handling related logic.
    void GameOver();

    // Resets the game state to start a new game.
    void Reset();

    // Initializes game entities and variables.
    void InitGame();

    // Checks if the current score is higher than the high score and updates it if necessary.
    void CheckForHighScore();

    // Saves the high score to a file for persistence.
    void saveHighScoreToFile(int highScore);

    // Loads the high score from a file at the start of the game.
    int loadHighScoreFromFile();

    // Private variables:

    // The player's spaceship.
    SpaceShip spaceship;

    // The mystery ship that appears occasionally.
    MysteryShip mysteryShip;

    // A heart representing an extra life for the spaceship.
    Heart spaceshipHeart;

    // A collection of obstacles in the game.
    std::vector<Obstacle> obstacles;

    // A collection of aliens in the game.
    std::vector<Alien> aliens;

    // The current direction of alien movement (e.g., left or right).
    int aliensDirecrion;

    // A collection of lasers fired by aliens.
    std::vector<Laser> alienLasers;

    // Time interval (in seconds) between consecutive alien laser shots.
    constexpr static float alienLaserShooterInterval = 0.35;

    // Tracks the time since the last alien fired a laser.
    float timeLastAlienFired;

    // Time interval (in seconds) for spawning the mystery ship.
    float mysteryShipSpawnInternal;

    // Time interval (in seconds) for spawning a heart.
    float heartSpawnInternal;

    // Tracks the time since the last mystery ship was spawned.
    float timeLastSpawnMysteryShip;

    // Tracks the time since the last heart was spawned.
    float timeLastSpawnHeart;

    // Sound effect played when an explosion occurs.
    Sound explosionSound;
};
