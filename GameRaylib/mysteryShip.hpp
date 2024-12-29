#pragma once
#include "raylib.h"

// Class representing the MysteryShip in the game
class MysteryShip {
public:
    // Constructor to initialize the MysteryShip object
    MysteryShip();

    // Destructor to clean up any resources used by the MysteryShip
    ~MysteryShip();

    // Method to update the state of the MysteryShip, typically called every frame
    void Update();

    // Method to draw the MysteryShip on the screen, usually called every frame
    void Draw() const;

    // Method to spawn a new MysteryShip at a specific location or state
    void Spawn();

    // Getter for the rectangle that bounds the MysteryShip, typically for collision detection
    Rectangle getRect();

    // Flag to indicate if the MysteryShip is alive (visible or functional in the game)
    bool alive;

private:
    // Position of the MysteryShip on the screen (2D vector)
    Vector2 position;

    // Texture to represent the image of the MysteryShip
    Texture2D image;

    // Speed of the MysteryShip, controlling how fast it moves
    int speed;
};


