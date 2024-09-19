#include "Infos.h"

Infos::Infos() {}

Infos::~Infos() {}

void Infos::addInfo(std::string info, int color)
{
	infosList.push_back(info);
	infosColorsList.push_back(color);

	if (infosList.size() > 6) {
		infosList.erase(infosList.begin());
		infosColorsList.erase(infosColorsList.begin());
	}
}

void Infos::updateInfos(int power, int life, int movement)
{
	std::cout << std::endl << "----------- Panel -----------" << std::endl << std::endl;

	std::cout << "Point de vie              ";
	setTextColor(10);
	std::cout << life << std::endl;
	resetTextColor();

	std::cout << "Point d'attaque           ";
	setTextColor(12);
	std::cout << power << std::endl;
	resetTextColor();

	std::cout << "Point de mouvement        ";
	setTextColor(11);
	std::cout << movement << std::endl << std::endl;
	resetTextColor();
	std::cout << "----------- Tchat -----------" << std::endl << std::endl;

    for (int i = 0; i < infosList.size(); i++) 
	{
		setTextColor(infosColorsList[i]);
        std::cout << infosList[i] << std::endl;
		resetTextColor();
    }
}

void Infos::setTextColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Infos::resetTextColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ((0 << 4) | 7));
}
