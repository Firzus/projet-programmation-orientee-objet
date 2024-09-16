#pragma once

#include <iostream>
#include <conio.h> 

#include "Dungeon.h"
#include "Hero.h"

class Game
{
	bool isPlaying;

	Dungeon dungeon;
	Hero hero;

public:
	Game();
	~Game();
	void init();
	void playTurn();
	void endGame();
};