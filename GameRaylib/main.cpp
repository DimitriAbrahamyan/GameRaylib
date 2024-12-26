// GameRaylib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "raylib.h"
#include "game.hpp"
#include "laser.hpp"
#include "obstacle.hpp"


int main() {
	Color grey = { 29,29,27,255 };
	int WindowWidth = 750;
	int WindowHeight = 700;
	
	InitWindow(WindowWidth, WindowHeight, "C++ Space Invaders");
	SetTargetFPS(60);

	Game game;

	while (!WindowShouldClose()) {
		game.HandleInput();
		game.Update();
		BeginDrawing();
			ClearBackground(grey);
			game.Draw();
		EndDrawing();
	}

	CloseWindow();
}


