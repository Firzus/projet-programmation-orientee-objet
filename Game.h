#pragma once
#include <iostream>

#include "Map.h"

class Game
{
	// attributs
	bool isPlaying;
	Map map;
public:
	Game();
	~Game();
	void init();
	void playTurn();
	void endGame();
};