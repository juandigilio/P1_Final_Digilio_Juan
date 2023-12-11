#pragma once

#include "Entity.h"

#include "ConsoleHandler.h"
#include "Bullet.h"

class Player : public Entity
{
private:

	int maxLives;
	int availableLives;
	int totalPoints;
	char input;
	bool isShooting;

public:

	Player(COORD position, COORD size, Color color, int refreshRate);
	~Player();

	void GetInput(ConsoleHandler* console);
	int GetAvailableLives() { return availableLives; }
	int GetTotalPoints() { return totalPoints; }
	char GetInput() { return input; }
	void SubstractLives() { availableLives--; }
	void AddPoints(int points) { totalPoints += points; }
	COORD GetLeftGunPos() { return { texture[0][3].position }; }
	COORD GetRightGunPos() { return texture[5][3].position; }
	bool IsShooting() { return isShooting; }
	Bullet** GetBullets(ConsoleHandler* console);

	void LoadTexture();
	void Move(ConsoleHandler* console);
	void CheckLimits(ConsoleHandler* console);
};
