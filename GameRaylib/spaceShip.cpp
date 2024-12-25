#include "spaceShip.hpp"

SpaceShip::SpaceShip() {
	image = LoadTexture("Graphics/spaceship.png");
	position.x = (static_cast<float>(GetScreenWidth())) / 2.25;
	position.y = GetScreenHeight() - image.height * 0.15;
	lastFireTime = 0.0;
}

SpaceShip::~SpaceShip() {
	UnloadTexture(image);
}

void SpaceShip::Draw() {
	DrawTextureEx(image, position, 0.0f, 0.1f,WHITE);
}

void SpaceShip::MoveLeft() {
	position.x -= 7;
	if (position.x < 0) {
		position.x = 0;
	}
}

void SpaceShip::MoveRight() {
	position.x += 7;
	if (position.x > GetScreenWidth() - image.width * 0.1) {
		position.x = GetScreenWidth() - image.width * 0.1;
	}
}

void SpaceShip::FireLaser() {
	if (GetTime() - lastFireTime >= 0.35) {
		lasers.push_back(Laser({ position.x + int(image.width * 0.1) / 2 - 2,position.y }, -6));
		lastFireTime = GetTime();
	}
}
