#pragma once

#include "Entity.h"

#include "ConsoleHandler.h"

class Player : public Entity
{
private:

	int maxLives;
	int availableLives;
	int totalPoints;
	char input;

public:

	Player(COORD position, COORD size, Color color);
	~Player();

	void GetInput(ConsoleHandler* console);
	bool UpdateStatus() { return availableLives; };
	int GetAvailableLives() { return availableLives; }
	int GetTotalPoints() { return totalPoints; }
	char GetInput() { return input; }
	void SubstractLives() { availableLives--; }
	COORD GetLeftGunPos() { return { texture[0][3].position }; }
	COORD GetRightGunPos() { return texture[5][3].position; }

	void AddPoints(int points) { totalPoints += points; }
	void AddLives(int lives);

	void LoadTexture();
	void Move(ConsoleHandler* console);
	void CheckLimits(ConsoleHandler* console);
};
