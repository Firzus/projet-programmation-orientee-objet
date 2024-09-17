#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Dungeon
{
	int index;
	std::vector<std::vector<std::string>> map;

public:
	Dungeon();
	~Dungeon();

	void loadRoom();
	void nextRoom();
	char checkPosition(int posX, int posY);
	std::vector<std::string> readRoom(std::string fileName);
	int getIndex() const { return index; }
	std::vector<std::vector<std::string>> getMap() { return map; }
	std::vector<std::string> getCurrentRoom();
	void updatePlayerPosition(int oldHeroPosX, int oldHeroPosY, int heroPosX, int heroPosY);
	void updateMapAfterEntityDeath(int x, int y);
};
