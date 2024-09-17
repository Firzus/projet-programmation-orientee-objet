#pragma once

#include <iostream>
#include <conio.h> 

#include "Dungeon.h"
#include "Hero.h"

class Game
{
	bool isPlaying = false;
	bool isWatchingUp = false;
	bool isWatchingDown = false;
	bool isWatchingLeft = false;
	bool isWatchingRight = false;

	Dungeon dungeon;
	Hero hero;

public:
	Game();
	~Game();
	void init();
	void playTurn();
	void endGame();
};