#include "Bullet.h"

Bullet::Bullet(COORD position, COORD size, Color color) : Entity(position, size, color)
{

}

Bullet::~Bullet()
{

}

void Bullet::LoadTexture()
{
	char textureToLoad[2][3] = {
	{'-','-','>'},
	{' ',' ',' '},
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

void Bullet::Move(ConsoleHandler* console)
{
	lastPos = actualPos;

	actualPos.X++;

	CheckLimits(console);

	UpdateTexturePositions();
}

void Bullet::CheckLimits(ConsoleHandler* console)
{
	int rightLimit = console->consoleWide - size.X - 1;

	if (actualPos.X > rightLimit)
	{
		isAlive = false;
		Clean(console);
	}
}
