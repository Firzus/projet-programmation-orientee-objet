#include "Dungeon.h"

Dungeon::Dungeon()
{
    index = 0;

	loadRoom();
}

Dungeon::~Dungeon(){}

void Dungeon::loadRoom()
{
    std::vector<std::string> roomOne = readRoom("room-one.txt");
    std::vector<std::string> roomTwo = readRoom("room-two.txt");
    std::vector<std::string> roomThree = readRoom("room-three.txt");

    map.push_back(roomOne);
    map.push_back(roomTwo);
    map.push_back(roomThree);
}

std::vector<std::string> Dungeon::readRoom(std::string fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << fileName << std::endl;
    }

    std::string ligne;
    std::vector<std::string> map;
    while (std::getline(file, ligne)) {
        map.push_back(ligne);
    }

    file.close();

    return map;
}

std::vector<std::string> Dungeon::getCurrentRoom()
{
    return map[index];
}

void Dungeon::updateMapAfterEntityDeath(int x, int y)
{
	map[index][y][x] = '.';
}

void Dungeon::updateSymbolAtPosition(int x, int y, char symbol)
{
	map[index][y][x] = symbol;
}

void Dungeon::nextRoom()
{
	if (index >= map.size()) {
		index = 0;
		return;
	}

	index++;
}

void Dungeon::updateTextInfos(std::string info)
{
    infosList.push_back(info);

	if (infosList.size() > 5) {
		infosList.erase(infosList.begin());
	}

	updateGame();
}

void Dungeon::updateGame()
{
	// Clear console
	system("cls");

	// Affichage de la room
    for (int i = 0; i < getCurrentRoom().size(); i++) {
        std::cout << getCurrentRoom()[i] << std::endl;
    }

	// Affichage des infos
    for (int i = 0; i < infosList.size(); i++) {
        std::cout << infosList[i] << std::endl;
    }
}

char Dungeon::checkPosition(int posX, int posY)
{
    if (index < 0 || index >= map.size()) {
        std::cerr << "Erreur : index de salle invalide" << std::endl;
        return '\0';
    }

    const std::vector<std::string>& currentRoom = map[index];
    if (posY < 0 || posY >= currentRoom.size() || posX < 0 || posX >= currentRoom[posY].size()) {
        std::cerr << "Erreur : coordonnées invalides" << std::endl;
        return '\0';
    }

    return currentRoom[posY][posX];
}