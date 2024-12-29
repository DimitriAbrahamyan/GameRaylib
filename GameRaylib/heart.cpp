#include "heart.hpp"

// Constructor for the Heart class, initializes the heart texture and sets its active state to false
Heart::Heart() {
    heartImage = LoadTexture("Graphics/heart.png");  // Load heart image from file
    active = false;  // Heart is initially inactive
}

// Destructor for the Heart class, unloads the heart texture
Heart::~Heart() {
    UnloadTexture(heartImage);  // Clean up texture resource
}

// Draws the heart if it is active
void Heart::Draw() const {
    if (active) {  // Only draw if the heart is active
        DrawTextureV(heartImage, position, WHITE);  // Draw heart texture at current position
    }
}

// Returns the rectangle representing the heart's collision box, if active
Rectangle Heart::getRect() const {
    if (active) {
        // Return a rectangle based on the heart's position and size
        return { position.x, position.y, float(heartImage.width), float(heartImage.height) };
    }
    else {
        // Return an empty rectangle if the heart is inactive
        return { position.x, position.y, 0, 0 };
    }
}

// Spawns a new heart at a random position near the top of the screen and makes it active
void Heart::Spawn() {
    position.y = GetRandomValue(85, 70);  // Set random y-position within range
    position.x = GetRandomValue(25, GetScreenWidth() - 25);  // Set random x-position within screen bounds
    speed = 3;  // Set the speed at which the heart will fall
    active = true;  // Make the heart active
}

// Updates the heart's position, making it fall downwards, and deactivates it if it moves off-screen
void Heart::Update() {
    if (active) {
        position.y += speed;  // Move the heart down by its speed value
        if (position.y < 25) {  // If the heart has fallen below the screen, deactivate it
            active = false;
        }
    }
}
