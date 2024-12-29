#pragma once
#include "raylib.h"

// The Laser class represents a laser beam fired by either the spaceship or an alien.
// It handles the laser's movement, rendering, and collision detection.
class Laser {
public:
    // Constructor: Initializes the laser's position and speed.
    Laser(Vector2 position, int speed);

    // Updates the laser's position and state.
    void Update();

    // Draws the laser on the screen if it is active.
    void Draw() const;

    // Returns the bounding rectangle of the laser, useful for collision detection.
    Rectangle getRect();

    // Indicates whether the laser is currently active (e.g., within screen bounds).
    bool active;

private:
    // The current position of the laser in the game world.
    Vector2 position;

    // The speed at which the laser moves (positive or negative depending on direction).
    int speed;
};
