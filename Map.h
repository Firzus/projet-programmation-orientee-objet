#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Map
{
	std::vector<std::vector<char>> map;

public:
	Map();
	~Map();
	void readFileMap();
	void displayMap();
};