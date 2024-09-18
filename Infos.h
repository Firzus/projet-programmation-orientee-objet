#pragma once

#include <vector>
#include <string>
#include <iostream>

class Infos
{
	std::vector<std::string> infosList;

public:
	Infos();
	~Infos();

	void addInfo(std::string info);
	void updateInfos();
};

