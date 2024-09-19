#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <windows.h>

class Infos
{
	std::vector<std::string> infosList;
	std::vector<int> infosColorsList;

public:
	Infos();
	~Infos();

	void addInfo(std::string info, int color);
	void updateInfos(int power, int life, int movement);
	void setTextColor(int color);
	void resetTextColor();
};

