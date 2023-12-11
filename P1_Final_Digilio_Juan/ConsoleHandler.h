#pragma once

#include <Windows.h>

enum Color
{
	grey = 8,
	blue = 9,
	green = 10,
	red = 12,
	violet = 13,
	yellow = 14,
	white = 15,
};

class ConsoleHandler
{
public:

	COORD cursorPosition;
	HANDLE hwnd;
	CONSOLE_FONT_INFOEX cfi;
	SMALL_RECT rect;
	COORD coord;
	CONSOLE_CURSOR_INFO cci;
	int consoleWide;
	int consoleHeight;
	int color;
	char userInput;

	COORD menu1;
	COORD menu2;
	COORD menu3;

	const COORD playerSize = { 4, 6 };
	const COORD asteroidSize = { 4, 4 };
	const COORD bulletSize = { 3, 2 };

	ConsoleHandler();
	~ConsoleHandler();

	void SetConsoleSize(int wide, int height);
	void SetConsoleFont(int wide, int height);
	void DrawFrame(int delay);
};

