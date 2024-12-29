#include "alien.hpp"

// Static array to store textures for the alien types
Texture2D Alien::alienImages[3] = {};

// Constructor to initialize the alien based on its type and position
Alien::Alien(int type, Vector2 position) {
    this->type = type;
    this->position = position;

    // Check if the texture for the given type is already loaded
    if (!alienImages[type - 1].id) {
        // Load the appropriate texture for the alien type
        switch (type) {
        case 1:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 2:
            alienImages[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 3:
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            break;
        default:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }
    }
}

// Update the alien's position based on the given direction (left or right)
void Alien::Update(int direction) {
    position.x += direction;
}

// Draw the alien at its current position using the corresponding texture
void Alien::Draw() const {
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

// Getter for the alien's type (1, 2, or 3)
int Alien::GetType() {
    return type;
}

// Unload all alien textures to free resources
void Alien::UnloadImages() {
    for (int i = 0; i < 3; ++i) {
        UnloadTexture(alienImages[i]);
    }
}

// Get the bounding rectangle of the alien, useful for collision detection
Rectangle Alien::getRect() {
    return { position.x, position.y,
             float(alienImages[type - 1].width),
             float(alienImages[type - 1].height)
    };
}
