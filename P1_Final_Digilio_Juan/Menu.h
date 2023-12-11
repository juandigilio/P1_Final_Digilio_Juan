#pragma once

#include "ConsoleHandler.h"

class Menu
{
private:

	int refreshRate;
	bool mainMenu;

public:

	Menu();
	~Menu();

	void ShowMain(ConsoleHandler* console);
	void ShowInstructions(ConsoleHandler* consoleData);
	void GetMenuInput(ConsoleHandler* consoleData);
};

