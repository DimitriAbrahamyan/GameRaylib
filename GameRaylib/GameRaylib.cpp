// GameRaylib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"
#include <iostream>


int main(void) {
	InitWindow(800, 450, R"(raylib [core] example - basic window)");

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();
}


