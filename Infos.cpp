#include "Infos.h"

Infos::Infos() {}

Infos::~Infos() {}

void Infos::addInfo(std::string info)
{
	infosList.push_back(info);

	if (infosList.size() > 6) {
		infosList.erase(infosList.begin());
	}
}

void Infos::updateInfos(int power, int life, int movement)
{
	std::cout << std::endl << "----------- Panel -----------" << std::endl << std::endl;

	std::cout << "Point de vie              " << life << std::endl;
	std::cout << "Point d'attaque           " << power << std::endl;
	std::cout << "Point de mouvement        " << movement << std::endl << std::endl;

	std::cout << "----------- Tchat -----------" << std::endl << std::endl;

    for (int i = 0; i < infosList.size(); i++) {
        std::cout << infosList[i] << std::endl;
    }
}
