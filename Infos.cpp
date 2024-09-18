#include "Infos.h"

Infos::Infos() {}

Infos::~Infos() {}

void Infos::addInfo(std::string info)
{
	infosList.push_back(info);

	if (infosList.size() > 10) {
		infosList.erase(infosList.begin());
	}
}

void Infos::updateInfos()
{
    for (int i = 0; i < infosList.size(); i++) {
        std::cout << infosList[i] << std::endl;
    }
}
