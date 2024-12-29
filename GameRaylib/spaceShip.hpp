#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

// Class representing the spaceship in the game
class SpaceShip {
public:
    // Constructor to initialize the spaceship object
    SpaceShip();

    // Destructor to clean up resources used by the spaceship
    ~SpaceShip();

    // Method to draw the spaceship on the screen
    void Draw() const;

    // Method to move the spaceship left
    void MoveLeft();

    // Method to move the spaceship right
    void MoveRight();

    // Method to fire a laser from the spaceship
    void FireLaser();

    // Getter for the rectangle that bounds the spaceship, typically used for collision detection
    Rectangle getRect();

    // Method to reset the spaceship to its initial position or state (e.g., after destruction)
    void Reset();

    // List of lasers currently fired by the spaceship
    std::vector<Laser> lasers;

private:
    // Texture representing the image of the spaceship
    Texture2D image;

    // Position of the spaceship on the screen (2D vector)
    Vector2 position;

    // Time of the last laser fire, used to control firing rate
    double lastFireTime;

    // Sound to play when firing a laser
    Sound laserSound;
};
