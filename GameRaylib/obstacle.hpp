#pragma once
#include <vector>
#include "block.hpp"

// Class representing an obstacle, composed of multiple blocks
class Obstacle {
public:
    // Constructor to initialize the Obstacle at a specific position
    Obstacle(Vector2 position);

    // Method to draw the obstacle on the screen
    void Draw();

    // Position of the obstacle on the screen (2D vector)
    Vector2 position;

    // Vector of blocks that make up the obstacle (each block is an individual part of the obstacle)
    std::vector<Block> blocks;

    // Static grid representing the layout of the obstacle, shared across all instances
    static std::vector<std::vector<int>> grid;
};
