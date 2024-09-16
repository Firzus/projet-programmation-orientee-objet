#pragma once
#include <iostream>

#include "Map.h"

class Game
{
	// attributs
	bool isPlaying;
public:
	Game();
	~Game();
	void init();
	void playTurn();
	void endGame();
};