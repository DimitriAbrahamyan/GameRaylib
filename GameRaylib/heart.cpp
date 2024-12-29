#include "heart.hpp"

Heart::Heart() {
	heartImage = LoadTexture("Graphics/heart.png");
	active = false;
}

Heart::~Heart() {
	UnloadTexture(heartImage);
}

void Heart::Draw() const {
	if (active) {
		DrawTextureV(heartImage, position, WHITE);
	}
}

Rectangle Heart::getRect() const {
	if (active) {
		return { position.x,position.y,float(heartImage.width),float(heartImage.height) };
	} else {
		return { position.x,position.y,0 ,0 };
	}
}

void Heart::Spawn() {
	position.y = GetRandomValue(85, 70);
	position.x = GetRandomValue(25, GetScreenWidth() - 25);
	speed = 3;
	active = true;
}

void Heart::Update() {
	if (active) {
		position.y += speed;
		if (position.y < 25) {
			active = false;
		}
	}
}