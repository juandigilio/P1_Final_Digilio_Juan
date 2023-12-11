#include "Player.h"

#include<iostream>
#include <conio.h>



using namespace std;

Player::Player(COORD position, COORD size, Color color, int refreshRate) : Entity(position, size, color, refreshRate)
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
		else if (input == 'Q')
		{
			isShooting = true;
		}
	}
}

Bullet** Player::GetBullets(ConsoleHandler* console)
{
	int bulletRefreshRate = 30;

	Bullet* left = new Bullet(GetLeftGunPos(), console->bulletSize, Color::grey, bulletRefreshRate);
	left->LoadTexture();
	Bullet* right = new Bullet(GetRightGunPos(), console->bulletSize, Color::grey, bulletRefreshRate);
	right->LoadTexture();

	Bullet* bullets[2];
	bullets[0] = left;
	bullets[1] = right;

	isShooting = false;

	return bullets;
}

void Player::LoadTexture()
{
	char textureToLoad[6][4] = {
	{' ',201,62,' '},
	{' ',186,' ',' '},
	{201,202,205,187},
	{200,203,205,188},
	{' ',186,' ',' '},
	{' ',200,62,' '},
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