#include "Game.h"

Game::Game()
{
	init();
}

Game::~Game(){}

void Game::init()
{
    // Init Hero
	
    // Init Monsters

	// then -> play the game
	playTurn();
}

void Game::playTurn()
{
    isPlaying = true;

    while (isPlaying) { // && hero.isAlive()
        // - Clear the console
        system("cls");

        // - Display map current state
        for (std::string line : dungeon.getCurrentRoom()) {
            std::cout << line << std::endl;
        }

        // Demande une action au joueur
        char action;

        std::cout << "Choose action: (arrow keys) move, (f)ight, (p)ause: ";
        action = _getch();

        // Gestion des actions du joueur
        if (action == -32) {
            action = _getch(); // Lire la touche suivante
            switch (action) {
            case 72: // Move up
                std::cout << "Choose up direction" << std::endl;
                // Set pos x, y

                std::cout << "Press any key to continue..." << std::endl;
                std::cin.get(); // Pause
                break;
            case 80: // Move down
                std::cout << "Choose down direction" << std::endl;
                // Set pos x, y

                std::cout << "Press any key to continue..." << std::endl;
                std::cin.get(); // Pause
                break;
            case 75: // Move left
                std::cout << "Choose left direction" << std::endl;
                // Set pos x, y

                std::cout << "Press any key to continue..." << std::endl;
                std::cin.get(); // Pause
                break;
            case 77: // Move right
                std::cout << "Choose right direction" << std::endl;
                // Set pos x, y

                std::cout << "Press any key to continue..." << std::endl;
                std::cin.get(); // Pause
                break;
            }
        }
        else {
            // Autres touches
            switch (action) {
            case 'f':
                std::cout << "Fight!" << std::endl;
                break;
            case 'p':
                isPlaying = false;
                break;
            case ' ':
                std::cout << "Special action triggered by space key!" << std::endl;

                std::cout << "Press any key to continue..." << std::endl;
                std::cin.get(); // Pause
                break;
            default:
                std::cout << "Invalid action! Please try again." << std::endl;
                break;
            }
        }
    }
}

void Game::endGame()
{    
	// Affiche un message de fin de jeu temporaire
	std::cout << "End Game" << std::endl;

    init();
}
