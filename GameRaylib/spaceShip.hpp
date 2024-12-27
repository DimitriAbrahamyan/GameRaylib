#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class SpaceShip {
public:
	SpaceShip();
	~SpaceShip();
	void Draw() const;
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	Rectangle getRect();
	std::vector<Laser> lasers;

private:
	Texture2D image;
	Vector2 position;
	double lastFireTime;
};