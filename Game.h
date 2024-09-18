#pragma once

#include <iostream>
#include <conio.h> 
#include <thread>
#include <chrono>

#include "Dungeon.h"
#include "Infos.h"
#include "Hero.h"
#include "Spectre.h"
#include "Faucheur.h"
#include "Golem.h"

class Game
{
	bool isPlaying = false;
	bool isWatchingUp = false;
	bool isWatchingDown = false;
	bool isWatchingLeft = false;
	bool isWatchingRight = false;

	Dungeon dungeon;
	Infos infos;
	Hero hero;
	std::vector<Spectre> spectres;
	std::vector<Faucheur> faucheurs;
	std::vector<Golem> golems;

public:
	Game();
	~Game();
	void init();
	void playTurn();
	void endGame();
	void getEntities();
	void updateGame();
	Entity* getEntityAtPosition(int x, int y);
	void updateEntityPosition(Entity* entity, int posX, int posY, int newPosX, int newPosY);
	void removeEntityAtPosition(int x, int y);
	void removeEnnemy(Entity* ennemy, int newPosX, int newPosY);
	bool areEnemiesRemaining();
	void playerTurn();
	void enemyTurn();
};