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
	std::vector<std::string> readRoom(std::string fileName);

	int getIndex() { return index; }
	void setIndex(int index) { this->index = index; }
	std::vector<std::vector<std::string>> getMap() { return map; }
	std::vector<std::string> getCurrentRoom();
};

