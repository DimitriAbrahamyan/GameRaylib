#include "mysteryShip.hpp"

// Constructor for the MysteryShip class, loads the texture and sets the ship to be inactive (not alive)
MysteryShip::MysteryShip() {
    image = LoadTexture("Graphics/mystery.png");  // Load the mystery ship's texture
    alive = false;  // Set the ship as not alive initially
}

// Destructor for the MysteryShip class, unloads the texture when the ship object is destroyed
MysteryShip::~MysteryShip() {
    UnloadTexture(image);  // Unload the texture to free up memory
}

// Updates the mystery ship's position and deactivates it if it goes out of screen bounds
void MysteryShip::Update() {
    if (alive) {  // Only update if the mystery ship is alive
        position.x += speed;  // Move the ship horizontally by the speed value
        // If the ship moves out of the screen (either left or right), set it to be inactive
        if (position.x > GetScreenWidth() - image.width || position.x < 0) {
            alive = false;  // Deactivate the mystery ship
        }
    }
}

// Draws the mystery ship on the screen if it is alive
void MysteryShip::Draw() const {
    if (alive) {  // Only draw if the ship is alive
        DrawTextureV(image, position, WHITE);  // Draw the ship at its position with the white color filter
    }
}

// Spawns the mystery ship at a random position, either on the left or right side of the screen
void MysteryShip::Spawn() {
    position.y = 90;  // Set the spawn position to be near the top of the screen
    int side = GetRandomValue(0, 1);  // Randomly decide whether the ship spawns on the left or right

    if (!side) {
        position.x = 25;  // Spawn on the left side
        speed = 3;        // Set the movement speed to positive (moving right)
    }
    else {
        position.x = GetScreenWidth() - image.width - 25;  // Spawn on the right side
        speed = -3;  // Set the movement speed to negative (moving left)
    }

    alive = true;  // Set the ship to be alive when it spawns
}

// Returns the rectangle representing the mystery ship's collision box
Rectangle MysteryShip::getRect() {
    if (alive) {
        return { position.x, position.y, float(image.width), float(image.height) };  // Return the ship's collision box
    }
    else {
        return { position.x, position.y, 0, 0 };  // If the ship is not alive, return an empty rectangle
    }
}