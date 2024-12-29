#include "block.hpp"

// Constructor to initialize a block at a specific position
Block::Block(Vector2 position) {
    this->position = position;
}

// Get the rectangle representing the block's position and size
Rectangle Block::getRect() const {
    Rectangle rect{};
    rect.x = position.x;  // X position of the block
    rect.y = position.y;  // Y position of the block
    rect.width = 3;       // Width of the block
    rect.height = 3;      // Height of the block

    return rect;
}

// Draw the block on the screen as a rectangle with a specific color
void Block::Draw() const {
    DrawRectangle(position.x, position.y, 3, 3, { 243, 216, 63, 255 }); // Draw a yellow block
}
