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
	void updateSymbolAtPosition(int x, int y, char symbol);
	void changeSymbolColor(int posX, int posY);
};
