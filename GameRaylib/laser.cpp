#include "laser.hpp"

// Constructor for the Laser class, initializes the laser's position, speed, and sets it as active
Laser::Laser(Vector2 position, int speed) {
    this->position = position;  // Set the initial position of the laser
    this->speed = speed;        // Set the speed at which the laser moves
    active = true;              // Set the laser to be active when created
}

// Draws the laser on screen if it is active
void Laser::Draw() const {
    if (active)  // Only draw the laser if it is active
        DrawRectangle(position.x, position.y, 4, 15, { 243,216,63,255 });  // Draw a rectangle to represent the laser
}

// Returns the rectangle representing the laser's collision box
Rectangle Laser::getRect() {
    Rectangle rect{};  // Initialize an empty rectangle
    rect.x = position.x;  // Set the x-coordinate based on laser's position
    rect.y = position.y;  // Set the y-coordinate based on laser's position
    rect.width = 4;        // Set the width of the laser's collision box
    rect.height = 15;      // Set the height of the laser's collision box

    return rect;  // Return the laser's rectangle
}

// Updates the laser's position, deactivating it if it moves out of the screen bounds
void Laser::Update() {
    position.y += speed;  // Move the laser vertically based on its speed
    if (active && (position.y > GetScreenHeight() - 100 || position.y < 25)) {
        active = false;  // If the laser is out of bounds (either at the bottom or top of the screen), deactivate it
    }
}
