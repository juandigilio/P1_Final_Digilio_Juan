#pragma once

#include "Entity.h"


using namespace std;

class Asteroid : public Entity
{
public:

	Asteroid(COORD position, COORD size, Color color, int refreshRate);
	~Asteroid();

	void LoadTexture();
	void Move(ConsoleHandler* console);
	void CheckLimits(ConsoleHandler* console);
	void SetRandPos(ConsoleHandler* console);
};