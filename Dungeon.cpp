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

void Dungeon::updateSymbolAtPosition(int x, int y, char symbol)
{
	map[index][y][x] = symbol;
}


void Dungeon::changeSelectedSymbolColor(int posX, int posY)
{
    char selectedSymbol = map[index][posY][posX];
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Save the actual position of the cursor
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    COORD originalPos = consoleInfo.dwCursorPosition;

    // Move the cursor to the symbol position
    SetConsoleCursorPosition(hConsole, { static_cast<SHORT>(posX), static_cast<SHORT>(posY) });

    // If the symbol selected is an emptySpace -> change background color to yellow
    if (map[index][posY][posX] == getEmptySpaceSymbol())
    {
        // Fuse background and text color (background color is the one between brackets)
        WORD color = (6 << 4) | 7;

        SetConsoleTextAttribute(hConsole, color);
        std::cout << getEmptySpaceSymbol();
    }
    // If the symbol selected is a random character, change its color directly
    else 
    {
        WORD color = (7 << 4) | 6;
        SetConsoleTextAttribute(hConsole, color);
        std::cout << selectedSymbol;
    }

    // Reinitialize color
    SetConsoleTextAttribute(hConsole, 7);

    // Put the cursor one line after its original position
    SetConsoleCursorPosition(hConsole, { static_cast<SHORT>(0), static_cast<SHORT>(originalPos.Y + 1) });
}

void Dungeon::nextRoom()
{
	if (index >= map.size()) {
		index = 0;
		return;
	}

	index++;
}

void Dungeon::updateRoom()
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < getCurrentRoom().size(); i++) 
    {
        // Check every character to see if they're an empty space
        for (int j = 0; j < getCurrentRoom()[i].size() ; j++)
        {
            char c = getCurrentRoom()[i][j];

            WORD color = (7 << 4) | 0;
            SetConsoleTextAttribute(hConsole, color);

            // Print the character
            std::cout << c;
        }
        // End of the string
        std::cout << std::endl;
    }

    // Reinitialize color
    SetConsoleTextAttribute(hConsole, 7);

}

char Dungeon::checkPosition(int posX, int posY)
{
    if (index < 0 || index >= map.size()) {
        std::cerr << "Erreur : index de salle invalide" << std::endl;
        return '\0';
    }

    const std::vector<std::string>& currentRoom = map[index];
    if (posY < 0 || posY >= currentRoom.size() || posX < 0 || posX >= currentRoom[posY].size()) {
        std::cerr << "Erreur : coordonn�es invalides" << std::endl;
        return '\0';
    }

    return currentRoom[posY][posX];
}
