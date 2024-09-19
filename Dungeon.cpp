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
	if (index >= map.size() - 1) {
		index = 0;
        map.clear();
        loadRoom();
		return;
	}

	index++;
}

void Dungeon::updateRoom(int heroPosX, int heroPosY, int PM)
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < getCurrentRoom().size(); i++) 
    {
        // Check every character to see if they're an empty space
        for (int j = 0; j < getCurrentRoom()[i].size() ; j++)
        {
            char c = getCurrentRoom()[i][j];

            // Check if the space is a space that can be visited by the player
            std::vector<std::vector<bool>> visited = getSpacesPlayerCanMove(heroPosX, heroPosY, PM);
            if (visited[i][j])
            {
                // If the space can be visited with current MP, color it in blue
                SetConsoleTextAttribute(hConsole, ((11 << 4) | 0));
            }
            else
            {
                SetConsoleTextAttribute(hConsole, ((7 << 4) | 0));
            }
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



std::vector<std::vector<bool>> Dungeon::getSpacesPlayerCanMove(int heroPosX, int heroPosY, int PM)
{
    const std::vector<std::pair<int, int>> directions = 
    {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Getting map height and width (only square map works for now)
    int height = map[index].size();
    int width = height > 0 ? map[index][0].size() : 0;

    // Vector to store visited spaces to avoid loops
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    // Creating a queue for BFS algorithm
    std::queue<std::tuple<int, int, int>> q;

    // Adding the space at player's position to visited spaces
    q.push({ heroPosX, heroPosY, 0 });
    visited[heroPosY][heroPosX] = true;

    // Making a BFS algorithm to go through spaces starting at player's position
    while (!q.empty()) {
        std::tuple<int, int, int> currentSpace = q.front();
        q.pop();

        int x = std::get<0>(currentSpace);
        int y = std::get<1>(currentSpace);
        int currentPM = std::get<2>(currentSpace);

        if (currentPM < PM) {
            for (size_t i = 0; i < directions.size(); ++i)
            {
                int newX = x + directions[i].first;
                int newY = y + directions[i].second;

                if (newX >= 0 && newX < width && newY >= 0 && newY < height && map[index][newY][newX] == getEmptySpaceSymbol() && !visited[newY][newX]) 
                {
                    visited[newY][newX] = true;
                    q.push({ newX, newY, currentPM + 1 });
                }
            }
        }
    }

    return visited;
}