#include "spaceShip.hpp"

SpaceShip::SpaceShip() {
	image = LoadTexture("Graphics/spaceship.png");
	position.x = (static_cast<float>(GetScreenWidth()) - image.width) / 2.0f;
	position.y = GetScreenHeight() - image.height - 100;
	lastFireTime = 0.0;
}

SpaceShip::~SpaceShip() {
	UnloadTexture(image);
}

void SpaceShip::Draw() const {
	DrawTextureV(image, position,WHITE);
}

void SpaceShip::MoveLeft() {
	position.x -= 7;
	if (position.x < 25) {
		position.x = 25;
	}
}

void SpaceShip::MoveRight() {
	position.x += 7;
	if (position.x > GetScreenWidth() - image.width - 25) {
		position.x = GetScreenWidth() - image.width - 25;
	}
}

void SpaceShip::FireLaser() {
	if (GetTime() - lastFireTime >= 0.35) {
		lasers.push_back(Laser({ position.x + image.width / 2 - 2,position.y }, -6));
		lastFireTime = GetTime();
	}
}

Rectangle SpaceShip::getRect() {
	return { position.x,position.y,float(image.width),float(image.height) };
}

void SpaceShip::Reset() {
	position.x = (static_cast<float>(GetScreenWidth()) - image.width) / 2.0f;
	position.y = GetScreenHeight() - image.height - 100;
	lasers.clear();
}
