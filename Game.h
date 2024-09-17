#pragma once

#include <iostream>
#include <conio.h> 

#include "Dungeon.h"
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
	Entity* getEntityAtPosition(int x, int y);
};