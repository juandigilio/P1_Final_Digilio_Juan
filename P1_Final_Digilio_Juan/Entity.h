#pragma once

#include <Windows.h>

#include "ConsoleHandler.h"
#include "Timer.h"

struct Texture
{
	char image;
	COORD position;
	bool isPainted;
};

class Entity
{
protected:

	COORD actualPos;
	COORD lastPos;
	COORD size;
	Texture** texture;
	Color color;
	bool isAlive;
	Timer* timer;
	int refreshRate;


public:

	Entity(COORD position, COORD size, Color color, int refreshRate);
	virtual ~Entity();

	void UpdateTexturePositions();
	void Draw(ConsoleHandler* console);
	void Clean(ConsoleHandler* console);
	void SetPosition(ConsoleHandler* console, COORD position);
	bool CheckCollision(Texture** entity, COORD size);
	COORD GetPosition() {return actualPos;}
	COORD GetSize() { return size; }
	Texture** GetTexture() { return texture; }
	bool CheckRefreshRate() { return timer->ElapsedTime(refreshRate); }
	bool IsAlive() { return isAlive; }
	void KillEntity() { isAlive = false; }


	virtual void LoadTexture() = 0;
	virtual void Move(ConsoleHandler* console) = 0;
	virtual void CheckLimits(ConsoleHandler* console) = 0;
};

