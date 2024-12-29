#include "spaceShip.hpp"

// Constructor for the SpaceShip class, which initializes the spaceship texture, position, and other attributes
SpaceShip::SpaceShip() {
    image = LoadTexture("Graphics/spaceship.png");  // Load the spaceship image texture
    position.x = (static_cast<float>(GetScreenWidth()) - image.width) / 2.0f;  // Set the initial X position at the center of the screen
    position.y = GetScreenHeight() - image.height - 100;  // Set the initial Y position near the bottom of the screen
    lastFireTime = 0.0;  // Initialize the time of the last laser fire to 0
    laserSound = LoadSound("Sounds/laser.ogg");  // Load the laser sound effect
}

// Destructor for the SpaceShip class, which unloads the spaceship texture and laser sound
SpaceShip::~SpaceShip() {
    UnloadTexture(image);  // Unload the spaceship image texture to free memory
    UnloadSound(laserSound);  // Unload the laser sound to free memory
}

// Draws the spaceship at its current position on the screen
void SpaceShip::Draw() const {
    DrawTextureV(image, position, WHITE);  // Draw the spaceship using its image at its position
}

// Moves the spaceship left by 7 pixels, ensuring it does not go beyond the left edge
void SpaceShip::MoveLeft() {
    position.x -= 7;  // Move spaceship left by 7 pixels
    if (position.x < 25) {  // Ensure the spaceship does not move past the left edge
        position.x = 25;
    }
}

// Moves the spaceship right by 7 pixels, ensuring it does not go beyond the right edge
void SpaceShip::MoveRight() {
    position.x += 7;  // Move spaceship right by 7 pixels
    if (position.x > GetScreenWidth() - image.width - 25) {  // Ensure the spaceship does not move past the right edge
        position.x = GetScreenWidth() - image.width - 25;
    }
}

// Fires a laser if enough time has passed since the last shot
void SpaceShip::FireLaser() {
    if (GetTime() - lastFireTime >= 0.35) {  // Check if 0.35 seconds have passed since the last fire
        lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -6));  // Create a new laser and add it to the lasers list
        lastFireTime = GetTime();  // Update the time of the last laser fire
        PlaySound(laserSound);  // Play the laser sound effect
    }
}

// Returns the rectangle representing the spaceship's bounding box for collision detection
Rectangle SpaceShip::getRect() {
    return { position.x, position.y, float(image.width), float(image.height) };  // Return a rectangle based on the spaceship's position and size
}

// Resets the spaceship to its initial position and clears the laser list
void SpaceShip::Reset() {
    position.x = (static_cast<float>(GetScreenWidth()) - image.width) / 2.0f;  // Reset X position to the center of the screen
    position.y = GetScreenHeight() - image.height - 100;  // Reset Y position near the bottom of the screen
    lasers.clear();  // Clear the list of lasers
}
