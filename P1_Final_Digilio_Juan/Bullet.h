#pragma once

#include "Entity.h"

class Bullet : Entity
{
public:

	Bullet(COORD position, COORD size, Color color);
	~Bullet();

	void LoadTexture();
	void Move(ConsoleHandler* console);
	void CheckLimits(ConsoleHandler* console);

};

