#pragma once

#include "raylib.h"

// The Heart class represents an extra life that can appear in the game.
// It handles the drawing, movement, and spawning of the heart.
class Heart {
public:
    // Constructor: Initializes the heart's properties.
    Heart();

    // Destructor: Cleans up resources such as the heart texture.
    ~Heart();

    // Draws the heart on the screen if it is active.
    void Draw() const;

    // Updates the heart's position and state.
    void Update();

    // Returns the bounding rectangle of the heart, useful for collision detection.
    Rectangle getRect() const;

    // Spawns the heart at a random position on the screen.
    void Spawn();

    // Indicates whether the heart is currently active in the game.
    bool active;

private:
    // The texture of the heart used for rendering.
    Texture2D heartImage;

    // The position of the heart in the game world.
    Vector2 position;

    // The speed at which the heart moves (if applicable).
    int speed;
};
