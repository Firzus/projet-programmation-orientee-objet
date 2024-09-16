#pragma once
#include <iostream>

#include "Dungeon.h"

class Game
{
	bool isPlaying;

	Dungeon dungeon;

public:
	Game();
	~Game();
	void init();
	void playTurn();
	void endGame();
};