#include "Player.h"

#include<iostream>
#include <conio.h>



using namespace std;

Player::Player(COORD position, COORD size, Color color) : Entity(position, size, color)
{
	maxLives = 6;
	availableLives = 3;
	totalPoints = 0;
}

Player::~Player()
{
	cout << "Player went to sleep" << endl;
}

void Player::GetInput(ConsoleHandler* console)
{
	if (_kbhit())
	{
		input = toupper(_getch());

		if (input == 27)
		{
			availableLives = 0;
		}
	}
}

void Player::AddLives(int lives)
{
	availableLives += lives;

	if (availableLives > 6)
	{
		availableLives = 6;
	}
}

void Player::LoadTexture()
{
	char textureToLoad[6][4] = {
	{' ',201,62,' '},
	{' ',186,' ',' '},
	{201,202,205,187},
	{200,203,205,187},
	{' ',186,' ',' '},
	{' ',200,62,' '},
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

void Player::Move(ConsoleHandler* console)
{
	lastPos = actualPos;

	if (input == 'S')
	{
		actualPos.Y++;

		CheckLimits(console);

		UpdateTexturePositions();
	}
	else if (input == 'W')
	{
		actualPos.Y--;

		CheckLimits(console);

		UpdateTexturePositions();
	}

	input = ' ';
}

void Player::CheckLimits(ConsoleHandler* console)
{
	int topLimit = 1;
	int bottomLimit = console->consoleHeight - size.Y - 2;

	if (actualPos.Y > bottomLimit)
	{
		actualPos.Y = bottomLimit;
	}
	else if (actualPos.Y < topLimit)
	{
		actualPos.Y = topLimit;
	}
}