#include "Entity.h"

#include <iostream>


using namespace std;


Entity::Entity(COORD position, COORD size, Color color, int refreshRate)
{
	this->actualPos = position;
	lastPos = actualPos;
	this->size = size;
	this->color = color;
	this->refreshRate = refreshRate;
	isAlive = true;
	
	texture = new Texture* [size.Y];

	for (int i = 0; i < size.Y; i++)
	{
		texture[i] = new Texture[size.X];
	}

	COORD aux = position;

	for (int i = 0; i < size.Y; i++)
	{
		for (int j = 0; j < size.X; j++)
		{
			texture[i][j].isPainted = false;
			texture[i][j].position.X = aux.X;
			texture[i][j].position.Y = aux.Y;
			aux.X++;
		}
		aux.X = position.X;
		aux.Y++;
	}

	timer = new Timer();
}

Entity::~Entity()
{
	delete[] texture;
	delete timer;
}

void Entity::UpdateTexturePositions()
{
	COORD aux = actualPos;

	for (int i = 0; i < size.Y; i++)
	{
		for (int j = 0; j < size.X; j++)
		{
			texture[i][j].position.X = aux.X;
			texture[i][j].position.Y = aux.Y;
			aux.X++;
		}
		aux.X = actualPos.X;
		aux.Y++;
	}
}

void Entity::Draw(ConsoleHandler* console)
{
	int leftLimit = 1;
	int rightLimit = console->consoleWide - 1;

	Clean(console);

	if (isAlive)
	{
		COORD cursorPos = actualPos;

		SetConsoleTextAttribute(console->hwnd, color);

		for (int i = 0; i < size.Y; i++)
		{
			SetConsoleCursorPosition(console->hwnd, cursorPos);

			for (int j = 0; j < size.X; j++)
			{
				if (texture[i][j].position.X > leftLimit && texture[i][j].position.X < rightLimit)
				{
					cout << texture[i][j].image;
				}
			}

			cursorPos.Y++;
		}
	}	
}

void Entity::Clean(ConsoleHandler* console)
{
	COORD cursorPos = lastPos;

	int leftLimit = 1;
	int rightLimit = console->consoleWide - 1;

	SetConsoleTextAttribute(console->hwnd, color);

	for (int i = 0; i < size.Y; i++)
	{
		SetConsoleCursorPosition(console->hwnd, cursorPos);	
		
		for (int j = 0; j < size.X; j++)
		{
			if (cursorPos.X + j > leftLimit && cursorPos.X + j < rightLimit)
			{
				cout << ' ';
			}
		}
		
		
		cursorPos.Y++;
	}

	lastPos = actualPos;
}

void Entity::SetPosition(ConsoleHandler* console, COORD newPosition)
{
	lastPos = actualPos;
	actualPos = newPosition;

	Clean(console);

	UpdateTexturePositions();
}

bool Entity::CheckCollision(Texture** entity, COORD entitySize)
{
	for (int i = 0; i < this->size.Y; i++)
	{
		for (int j = 0; j < this->size.X; j++)
		{
			for (int k = 0; k < entitySize.Y; k++)
			{
				for (int l = 0; l < entitySize.X; l++)
				{
					if (this->texture[i][j].isPainted && entity[k][l].isPainted)
					{
						bool x = (this->texture[i][j].position.X == entity[k][l].position.X);
						bool y = (this->texture[i][j].position.Y == entity[k][l].position.Y);

						if (x && y)
						{
							return true;
						}
					}			
				}
			}
		}
	}

	return false;
}
