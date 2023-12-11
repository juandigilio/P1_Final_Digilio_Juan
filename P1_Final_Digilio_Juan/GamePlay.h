#pragma once

#include "Timer.h"
#include "ConsoleHandler.h"
#include "Menu.h"
#include "Entity.h"
#include "Player.h"
#include "HUD.h"

#include <vector>

using namespace std;

static const int shootingPoints = 50;

class GamePlay
{
private:

	Timer* frameTimer;
	Timer* enemySpawn;
	ConsoleHandler* console;
	Menu* menu;
	Player* player;
	vector<Entity*> entities;
	HUD* hud;

	bool keepPlaying;
	bool firstTime = true;

public:

	GamePlay();
	~GamePlay();

	void RunGame();
	void GameLoop();
	void UpadateCollisions();
	void Update();
	void ResetGame();
	void ManageEnemies();
	void CheckWiningCondition();
	void ClearDeathEntities();
};

