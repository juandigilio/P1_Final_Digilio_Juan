#include "Menu.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>



using namespace std;

Menu::Menu()
{
	refreshRate = 50;
	mainMenu = false;
}

Menu::~Menu()
{

}

void Menu::ShowMain(ConsoleHandler* consoleData)
{
	string welcome = ">>Wellcome to the last ride<<";
	string option1 = "1- New game";
	string option2 = "2- Instructions";
	string option3 = "ESC - Exit";
	string clean = "                               ";
	COORD thisCursor{};

	bool mainMenu = true;

	system("cls");

	consoleData->DrawFrame(0);

	thisCursor.X = (consoleData->consoleWide / 2) - (welcome.length() / 2);
	thisCursor.Y = (consoleData->consoleHeight / 20) * 8;
	SetConsoleTextAttribute(consoleData->hwnd, 10);
	SetConsoleCursorPosition(consoleData->hwnd, thisCursor);
	cout << welcome;

	consoleData->menu1 = thisCursor;

	thisCursor.X = (consoleData->consoleWide / 2) - (option1.length() / 2);
	thisCursor.Y = (consoleData->consoleHeight / 20) * 14;
	SetConsoleTextAttribute(consoleData->hwnd, 12);
	SetConsoleCursorPosition(consoleData->hwnd, thisCursor);
	cout << option1;

	consoleData->menu2 = thisCursor;

	thisCursor.X = (consoleData->consoleWide / 2) - (option2.length() / 2);
	thisCursor.Y = (consoleData->consoleHeight / 20) * 16;
	SetConsoleTextAttribute(consoleData->hwnd, 14);
	SetConsoleCursorPosition(consoleData->hwnd, thisCursor);
	cout << option2;

	consoleData->menu3 = thisCursor;

	thisCursor.X = (consoleData->consoleWide / 2) - (option3.length() / 2);
	thisCursor.Y = (consoleData->consoleHeight / 20) * 18;
	SetConsoleTextAttribute(consoleData->hwnd, 9);
	SetConsoleCursorPosition(consoleData->hwnd, thisCursor);
	cout << option3;
}

void Menu::ShowInstructions(ConsoleHandler* consoleData)
{
	string inst1 = "W/S to move and Q to shoot...";
	string clean = "                                   ";

	system("cls");

	consoleData->DrawFrame(0);

	consoleData->cursorPosition.X = (consoleData->consoleWide / 2) - (inst1.length() / 2);
	consoleData->cursorPosition.Y = (consoleData->consoleHeight / 2) - 4;
	SetConsoleCursorPosition(consoleData->hwnd, consoleData->cursorPosition);
	SetConsoleTextAttribute(consoleData->hwnd, 14);
	cout << inst1;

	while (consoleData->userInput != 27)
	{
		consoleData->userInput = _getch();
	}

	consoleData->userInput = '0';

	consoleData->cursorPosition.X = (consoleData->consoleWide / 2) - (inst1.length() / 2);
	consoleData->cursorPosition.Y = (consoleData->consoleHeight / 2) - 4;
	SetConsoleTextAttribute(consoleData->hwnd, 14);
	SetConsoleCursorPosition(consoleData->hwnd, consoleData->cursorPosition);
	cout << clean;
}

void Menu::GetMenuInput(ConsoleHandler* consoleData)
{
	while (consoleData->userInput != '1' && consoleData->userInput != '2' && consoleData->userInput != 27)
	{
		consoleData->userInput = _getch();
	}
}

