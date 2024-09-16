#include "Dungeon.h"

Dungeon::Dungeon()
{
    index = 0;
}

Dungeon::~Dungeon(){}

void Dungeon::loadRoom()
{
    // TODO: Change maps values
    std::vector<std::string> roomOne = readRoom("room-one.txt");
    std::vector<std::string> roomTwo = readRoom("room-one.txt");
    std::vector<std::string> roomThree = readRoom("room-one.txt");

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