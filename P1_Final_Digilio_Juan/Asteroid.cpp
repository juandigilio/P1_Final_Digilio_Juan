#include "Asteroid.h"

#include <iostream>
#include <Windows.h>

#include "ConsoleHandler.h"

using namespace std;


Asteroid::Asteroid(COORD position, COORD size, Color color, int refreshRate) : Entity(position, size, color, refreshRate)
{

}

Asteroid::~Asteroid()
{

}

void Asteroid::LoadTexture()
{
	char textureToLoad[4][4] = {
	{' ','*','*',' '},
	{'*','*','*','*'},
	{'*','*','*','*'},
	{' ','*','*',' '},
	};

	for (int i = 0; i < size.Y; i++)
	{
		for (int j = 0; j < size.X; j++)
		{
			texture[i][j].image = textureToLoad[i][j];

			if (texture[i][j].image != ' ')
			{
				texture[i][j].isPainted = true;
			}
		}
	}

	UpdateTexturePositions();
}

void Asteroid::Move(ConsoleHandler* console)
{
	lastPos = actualPos;

	actualPos.X--;

	CheckLimits(console);

	UpdateTexturePositions();
}

void Asteroid::CheckLimits(ConsoleHandler* console)
{
	int leftLimit = 1;

	if (actualPos.X < leftLimit)
	{
		Clean(console);
		actualPos.X = leftLimit;
		isAlive = false;
	}
}

void Asteroid::SetRandPos(ConsoleHandler* console)
{
	srand(time(NULL));

	int y = (rand() % (console->consoleHeight - 6)) + 2;

	COORD newPos{ console->consoleWide - 1,  y };

	SetPosition(console, newPos);
}
