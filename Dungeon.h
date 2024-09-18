#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

class Dungeon
{
	int index;
	std::vector<std::vector<std::string>> map;
	std::vector<std::string> infosList;
	char wall = '#';
	char emptySpace = ' ';

public:
	Dungeon();
	~Dungeon();

	void loadRoom();
	void nextRoom();
	void updateTextInfos(std::string info);
	void updateGame();
	char checkPosition(int posX, int posY);
	std::vector<std::string> readRoom(std::string fileName);
	int getIndex() const { return index; }
	std::vector<std::vector<std::string>> getMap() { return map; }
	std::vector<std::string> getCurrentRoom();
	void updatePlayerPosition(int oldHeroPosX, int oldHeroPosY, int heroPosX, int heroPosY);
	void updateMapAfterEntityDeath(int x, int y);
	void changeSelectedSymbolColor(int posX, int posY);
	char getWallSymbol() const { return wall; }
	char getEmptySpaceSymbol() const { return emptySpace; }
};
