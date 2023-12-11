#include "GamePlay.h"

#include <iostream>
#include <conio.h>

#include "Asteroid.h"
#include "Bullet.h"


GamePlay::GamePlay()
{
	srand(time(nullptr));

	frameTimer = new Timer();
	enemySpawn = new Timer();

	console = new ConsoleHandler();
	console->SetConsoleFont(20, 25);
	console->SetConsoleSize(console->consoleWide, console->consoleHeight);

	menu = new Menu();

	COORD playerPos{ 2, console->consoleHeight / 2 };
	const int playerRefreshRate = 50;
	player = new Player(playerPos, console->playerSize, Color::red, playerRefreshRate);
	player->LoadTexture();

	entities.push_back(player);

	hud = new HUD(console);
}

GamePlay::~GamePlay()
{
	delete frameTimer;
	delete enemySpawn;
	delete console;
	delete menu;

	ClearDeathEntities();

	for (auto& entity : entities)
	{
		if (entity != nullptr)
		{
			delete entity;
		}
	}

	entities.clear();
}

void GamePlay::RunGame()
{
	srand(time(NULL));

	keepPlaying = true;
	bool mainMenu = true;

	console->userInput = '0';

	while (keepPlaying)
	{
		while (mainMenu)
		{
			switch (console->userInput)
			{
			case '0':
			{
				menu->ShowMain(console);
				break;
			}
			case '1':
			{
				mainMenu = false;
				break;
			}
			case '2':
			{
				menu->ShowInstructions(console);
				break;
			}
			case 27:
			{
				keepPlaying = false;
				break;
			}
			}

			if (keepPlaying && mainMenu)
			{
				menu->GetMenuInput(console);
			}

			if (console->userInput == '1')
			{
				system("cls");

				GameLoop();

				system("cls");

				hud->ShowHud(console, player);
				CheckWiningCondition();
				keepPlaying = false;
			}
		}
	}
}

void GamePlay::GameLoop()
{
	console->DrawFrame(0);

	hud->ShowHud(console, player);

	while (player->GetAvailableLives() > 0 && player->GetTotalPoints() < 1000)
	{
		player->GetInput(console);

		Update();
	}
}

void GamePlay::UpadateCollisions()
{
	bool isCollision = false;

	for (auto& entity : entities)
	{
		if (!isCollision)
		{
			Asteroid* aux = dynamic_cast<Asteroid*>(entity);

			if (aux != nullptr)
			{
				for (auto& entity2 : entities)
				{
					Player* aux2 = dynamic_cast<Player*>(entity2);

					if (aux2 != nullptr)
					{
						if (aux->CheckCollision(aux2->GetTexture(), aux2->GetSize()))
						{
							aux2->SubstractLives();

							ResetGame();
							hud->UpdateHud(console, player);

							isCollision = true;
							break;
						}
					}
					else
					{
						Entity* aux3 = dynamic_cast<Bullet*>(entity2);

						if (aux3 != nullptr)
						{
							if (aux->CheckCollision(aux3->GetTexture(), aux3->GetSize()))
							{
								aux->Clean(console);
								aux3->Clean(console);

								aux->KillEntity();
								aux3->KillEntity();

								player->AddPoints(shootingPoints);

								hud->UpdateHud(console, player);

								isCollision = true;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void GamePlay::Update()
{
	if (player->GetAvailableLives() <= 0)
	{
		keepPlaying = false;
	}
	else
	{
		ManageEnemies();

		for (auto& entity : entities)
		{
			if (entity->CheckRefreshRate())
			{
				entity->Move(console);
				entity->Draw(console);
			}
		}

		if (player->IsShooting())
		{
			Bullet** bullets = player->GetBullets(console);

			entities.push_back(bullets[0]);
			entities.push_back(bullets[1]);
		}

		UpadateCollisions();

		ClearDeathEntities();
	}
}

void GamePlay::ResetGame()
{
	COORD center = { 2, console->consoleHeight / 2 };

	for (auto& entity : entities)
	{
		entity->Clean(console);

		Player* aux = dynamic_cast<Player*>(entity);

		if (aux == nullptr)
		{
			delete entity;
		}
	}

	entities.clear();

	player->SetPosition(console, center);

	entities.push_back(player);
}

void GamePlay::ManageEnemies()
{
	int asteroidsRefreshRate = 70;

	if (enemySpawn->ElapsedTime(5000))
	{
		Asteroid* asteroid = new Asteroid({ 0, 0 }, console->asteroidSize, Color::grey, asteroidsRefreshRate);
		asteroid->SetRandPos(console);
		asteroid->LoadTexture();
		entities.push_back(asteroid);
	}
}

void GamePlay::CheckWiningCondition()
{
	COORD cursor{ console->consoleWide / 2 - 5, console->consoleHeight / 2 };

	SetConsoleCursorPosition(console->hwnd, cursor);

	if (player->GetAvailableLives() <= 0)
	{
		cout << "Perdiste!";
		cursor.Y += 3;
		SetConsoleCursorPosition(console->hwnd, cursor);
		cout << "Salir-ESC";
	}
	else
	{
		cout << "Ganaste!";
		cursor.Y += 3;
		cursor.X--;
		SetConsoleCursorPosition(console->hwnd, cursor);
		cout << "Salir-ESC";
	}
}

void GamePlay::ClearDeathEntities()
{
	vector<Entity*> aliveEntities;

	for (auto& entity : entities)
	{
		if (entity != nullptr && entity->IsAlive())
		{
			aliveEntities.push_back(entity);
		}
		else
		{
			delete entity;
		}
	}

	entities.clear();

	for (auto& entity : aliveEntities)
	{
		entities.push_back(entity);
	}
}
