#pragma once
#include "raylib.h"

// The Alien class represents an alien entity in the game. It includes attributes
// such as type and position, as well as methods to update, draw, and manage the alien.
class Alien {
public:
    // Constructor: Initializes the alien with a specific type and position.
    Alien(int type, Vector2 position);

    // Updates the alien's position based on the given direction.
    // 'direction' could indicate movement left, right, or none.
    void Update(int direction);

    // Draws the alien on the screen using its type and position.
    void Draw() const;

    // Returns the type of the alien 
    int GetType();

    // Static method to unload all alien images from memory.
    static void UnloadImages();

    // Returns the bounding rectangle of the alien, useful for collision detection.
    Rectangle getRect();

    // Static array to hold textures for different types of aliens (up to 3 types).
    static Texture2D alienImages[3];

    // Public member variables:
    // 'type' indicates the type of alien (e.g., used to differentiate between images).
    int type;
    
    // 'position' holds the alien's current position in the game world.
    Vector2 position;
};
