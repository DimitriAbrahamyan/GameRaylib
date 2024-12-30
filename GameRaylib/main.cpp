#include <raylib.h>
#include "game.hpp"
#include <string>

// Helper function to format a number with leading zeros to match a specified width
static std::string FormatWithLeadingZero(int number, int width) {
    std::string numberText = std::to_string(number);  // Convert number to string
    int leadingZero = width - numberText.length();  // Calculate how many leading zeros are needed
    numberText = std::string(leadingZero, '0') + numberText;  // Add leading zeros to the number string

    return numberText;
}

int main() {
    // Define color constants for UI elements
    Color grey = { 29, 29, 27, 255 };  // Background color
    Color yellow = { 243, 216, 63, 255 };  // Text and UI highlight color

    // Set window size and offset for padding
    int WindowWidth = 750;
    int WindowHeight = 700;
    int offset = 50;

    // Initialize the game window and audio device
    InitWindow(WindowWidth + offset, WindowHeight + 2 * offset, "C++ Space Invaders");
    InitAudioDevice();

    // Load font and spaceship image for UI and rendering
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);  // Load custom font for text rendering
    Texture2D spaceShipImage = LoadTexture("Graphics/spaceship.png");  // Load the spaceship image for lives display

    // Set the frame rate for the game loop
    SetTargetFPS(60);

    // Initialize the game object which will handle game logic
    Game game;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update the music stream and game states
        UpdateMusicStream(game.music);  // Update background music if any
        game.HandleInput();  // Handle player inputs (keyboard, mouse, etc.)
        game.Update();  // Update game state (logic, movements, collisions, etc.)

        // Begin drawing and rendering
        BeginDrawing();
        ClearBackground(grey);  // Clear screen with the grey background color

        // Draw a rounded rectangle border for the main game area
        DrawRectangleRoundedLines({ 10, 10, 780, 780 }, 0.18f, 20, yellow);

        // Draw a line at the bottom to separate the UI from the game area
        DrawLineEx({ 25, 730 }, { 775, 730 }, 3, yellow);

        // Display either "LEVEL 01" or "GAME OVER" depending on the game state
        if (!game.CheckForWinGame())
        {
            if (game.run) {
                DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 2, yellow);  // Show level text if the game is running
            }
            else {
                DrawTextEx(font, "GAME OVER", { 570, 740 }, 34, 2, yellow);  // Show "Game Over" text if the game has ended
            }
        }
        else {
            DrawTextEx(font, "WIN GAME", { 570,740 }, 34, 2, yellow);
        }


        // Draw lives (spaceships) at the bottom of the screen
        float x = 50.0f;
        for (int i = 0; i < game.lives; ++i) {
            DrawTextureV(spaceShipImage, { x, 745 }, WHITE);  // Draw spaceship image for each life
            x += 50;  // Adjust X position for next life icon
        }

        // Display score
        DrawTextEx(font, "Score", { 50, 15 }, 34, 2, yellow);  // Display "Score" label
        std::string scoreText = FormatWithLeadingZero(game.score, 5);  // Format the score with leading zeros
        DrawTextEx(font, scoreText.c_str(), { 50, 40 }, 34, 2, yellow);  // Display the formatted score

        // Display high score
        DrawTextEx(font, "BEST SCORE", { 570, 15 }, 34, 2, yellow);  // Display "HIGH-SCORE" label
        std::string highScoreText = FormatWithLeadingZero(game.highScore, 5);  // Format the high score with leading zeros
        DrawTextEx(font, highScoreText.c_str(), { 655, 40 }, 34, 2, yellow);  // Display the formatted high score

        // Call the game object's draw method to render the game elements
        game.Draw();
        EndDrawing();
    }

    // Clean up and close resources when the window is closed
    CloseWindow();  // Close the game window
    CloseAudioDevice();  // Close the audio device to stop music and free resources
}
