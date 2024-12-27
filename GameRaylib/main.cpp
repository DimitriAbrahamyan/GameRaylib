// GameRaylib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <raylib.h>
#include "game.hpp"



int main() {
	Color grey = { 29,29,27,255 };
	Color yellow = { 243,216,63,255 };
	int WindowWidth = 750;
	int WindowHeight = 700;
	int offset = 50;
	
	InitWindow(WindowWidth + offset, WindowHeight + 2 * offset, "C++ Space Invaders");

	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);	
	Texture2D spaceShipImage = LoadTexture("Graphics/spaceship.png");

	SetTargetFPS(60);

	Game game;


	while (!WindowShouldClose()) {
		game.HandleInput();
		game.Update();
		BeginDrawing();
			ClearBackground(grey);
			DrawRectangleRoundedLines({ 10, 10, 780, 780 }, 0.18f, 20, yellow);
			DrawLineEx({ 25,730 }, { 775,730 }, 3, yellow);
			if (game.run) {
				DrawTextEx(font, "LEVEL 01", { 570,740 }, 34, 2, yellow);
			}
			else {
				DrawTextEx(font, "GAME OVER", { 570,740 }, 34, 2, yellow);
			}
			float x = 50.0f;
			for (int i = 0; i < game.lives; ++i) {
				DrawTextureV(spaceShipImage, { x,745 }, WHITE);
				x += 50;
			}

			game.Draw();
		EndDrawing();
	}

	CloseWindow();
}


