# Space Invaders

Space Invaders is a retro-style arcade game built using the Raylib library. This project is a simple implementation of the classic Space Invaders game, where players control a spaceship, avoid enemy fire, and score points by shooting enemies.

## Features

- **Spaceship Control**: Move the spaceship left and right to dodge enemy attacks.
- **Laser Firing**: Fire lasers to destroy enemies.
- **Score System**: Tracks the player's score and maintains the best score.
- **Game Levels**: Start with Level 1 and survive as long as possible(The game currently has only one level; the other levels are in development).
- **Lives System**: Lose a life when hit, and the game ends when all lives are lost.
- **Custom UI**: Displays current score, the best score, lives, and game level.


## How to play

1. Objective:
    - Control your spaceship to avoid enemy fire and destroy enemies to score points.

2. Game Controls:
    - Move Left: Press the left arrow key.
    - Move Right: Press the right arrow key.
    - Fire Laser: Press the spacebar.
    
3. Game Loop:
    - Survive as long as possible by dodging enemy fire and firing back.
    - Gain points for each enemy destroyed.
    - Lose a life when hit by enemy fire. The game ends when all lives are lost.

4. Score:
    - Your score is displayed in the top-left corner.
    - The best score is displayed in the top-right corner and persists across games.

5. Lives:
    - Lives are represented by spaceship icons at the bottom-left of the screen.


## Directories

1. Graphics/
    - Contains all image assets used in the game.
    - spaceship.png: The sprite image for the player's spaceship.

2. Sounds/
    - Contains sound effects used in the game.
    - laser.ogg: The sound effect played when the spaceship fires a laser.

3. Font/
    - Contains font assets used for displaying text in the game.
    - monogram.ttf: The font used for the game's UI, such as score and level text.


## Source files

1. main.cpp
    -  The entry point of the program. Initializes the game window, manages the game loop, and handles UI rendering.
2. game.cpp
    - Implements the Game class, which manages the overall game state, including levels, score, lives, and interactions between objects.
3. game.hpp
    - Header file for the Game class, declaring its properties and methods.
4. spaceship.cpp
    - Implements the SpaceShip class, handling player-controlled spaceship movement, laser firing, and resetting its state.
5. spaceship.hpp
    - Header file for the SpaceShip class, defining its properties and methods.
6. laser.cpp
    - Implements the Laser class, managing the behavior of lasers fired by the spaceship or aliens.
7. laser.hpp
    - Header file for the Laser class, declaring its properties and methods.
8. alien.cpp
    - Implements the Alien class, handling the behavior of aliens, including movement and collision detection.
9. alien.hpp
    - Header file for the Alien class, defining the properties and methods of aliens.


## Requirements

- **C++17 or later**
- **Raylib** library installed
- **Compiler**: GCC, Clang, or MSVC
- **Assets**:
  - `Graphics/spaceship.png` for the spaceship sprite
  - `Font/monogram.ttf` for the game font
  - `Sounds/laser.ogg` for the laser firing sound

## Adding Raylib to Visual Studio

1. Download Raylib
    - Go to the Raylib GitHub repository (https://github.com/raysan5/raylib) or the official website (https://www.raylib.com).
    - Download the latest release for game.

2. Set up Visual Studio
    - Open Visual Studio and create a new C++ project.
    -  Go to Project > Properties.

3. Configure Include and Library Paths
    - Under Configuration Properties, select VC++ Directories.
    - Set the Include Directories to point to Raylib's include folder.
    - Set the Library Directories to point to Raylib's lib folder.

4. Link Raylib
    - Under Configuration Properties, go to Linker > Input.
    -  Add the following libraries to the Additional Dependencies field:
        -  raylib.lib
        - For some platforms, you might also need:
            opengl32.lib, winrm.lib, kernel32.lib, gdi32.lib, and user32.lib.

5. Copy DLL Files (Windows Only)
    - If you are using Windows, copy the Raylib .dll files (found in the bin folder) to your project's output directory (usually the Debug or Release folder).

6. Test Raylib
    - Include the Raylib header in your main file:
        ``` cpp
        #include <raylib.h>

    - Write a simple program to ensure everything is working:
        ``` cpp
        int main() {
            InitWindow(800, 600, "Hello, Raylib!");
            while (!WindowShouldClose()) {
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawText("Welcome to Raylib!", 190, 200, 20, LIGHTGRAY);
                EndDrawing();
            }
            CloseWindow();
            return 0;
        }

    - Build and run your project.
        - After a successful build, click the Local Windows Debugger button at the top (or press F5) to run your project.
            - If you selected Release configuration, use the Start Without Debugging option (Ctrl + F5) for better performance.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/cpp-space-invaders.git
   cd cpp-space-invaders
2. Build the project:
    ```bash
    g++ -o space_invaders main.cpp game.cpp spaceship.cpp laser.cpp alien.cpp -lraylib -std=c++17
3. Run the game
    ```bash
    ./space_invaders
# License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.

