#include "Asteroid.h"

#include <iostream>
#include <Windows.h>

#include "ConsoleHandler.h"

using namespace std;


Asteroid::Asteroid(COORD position, COORD size, Color color) : Entity(position, size, color)
{

}

Asteroid::~Asteroid()
{
	cout << "Enemy deleted!";
}

void Asteroid::LoadTexture()
{
	char textureToLoad[3][3] = {
	{' ','O',' '},
	{'/','|',92},
	{'/',' ',92},
	};

	for (int i = 0; i < size.X; i++)
	{
		for (int j = 0; j < size.Y; j++)
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
		isAlive = false;
		Clean(console);
	}
}

void Asteroid::SetRandPos(ConsoleHandler* console)
{
	srand(time(NULL));

	COORD newPos{ console->consoleWide - 2, (rand() % console->consoleHeight - 4) + 2 };

	SetPosition(console, newPos);
}
