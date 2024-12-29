#pragma once
#include "raylib.h"

// The Block class represents a static block in the game. It includes attributes
// like position and methods to get its rectangle and draw it on the screen.
class Block {
public:
    // Constructor: Initializes the block at a specific position.
    Block(Vector2 position);

    // Returns the bounding rectangle of the block, useful for collision detection.
    Rectangle getRect() const;

    // Draws the block on the screen at its current position.
    void Draw() const;

private:
    // 'position' holds the block's current position in the game world.
    Vector2 position;
};
