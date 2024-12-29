#pragma once

#include "raylib.h"


class Heart {
public:
	Heart();
	~Heart();
	void Draw() const;
	void Update();
	Rectangle getRect() const;
	void Spawn();
	bool active;
private:
	Texture2D heartImage;
	Vector2 position;
	int speed;
};
