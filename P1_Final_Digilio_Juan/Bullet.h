#pragma once

#include "Entity.h"

class Bullet : public Entity
{
public:

	Bullet(COORD position, COORD size, Color color, int refreshRate);
	~Bullet();

	void LoadTexture();
	void Move(ConsoleHandler* console);
	void CheckLimits(ConsoleHandler* console);
};

