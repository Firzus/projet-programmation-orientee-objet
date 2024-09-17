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
	std::vector<std::string> readRoom(std::string fileName);
	int getIndex() const { return index; }
	std::vector<std::vector<std::string>> getMap() { return map; }
	std::vector<std::string> getCurrentRoom();
};
