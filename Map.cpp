#include "Map.h"

Map::Map()
{

}

Map::~Map(){}

void Map::readFileMap()
{
    std::string filename = "map.txt";
    std::ifstream file(filename);

    // Vérifier si le fichier a été ouvert correctement
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }

    std::string ligne;
    while (std::getline(file, ligne)) {
        std::vector<char> ligneVec(ligne.begin(), ligne.end());
        map.push_back(ligneVec);
    }

    file.close();
}

void Map::displayMap()
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}
