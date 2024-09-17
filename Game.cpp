#include "Game.h"

Game::Game()
{
	init();
}

Game::~Game(){}

void Game::init()
{
    // Init Hero
	hero.setPos(dungeon.getCurrentRoom());
	
    // Init Monsters

	// then -> play the game
	playTurn();
}

void Game::playTurn()
{
    isPlaying = true;

    while (isPlaying && hero.isAlive()) {
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
				isWatchingUp = true;

                break;
            case 80: // Move down
                std::cout << "Choose down direction" << std::endl;
				isWatchingDown = true;

                break;
            case 75: // Move left
                std::cout << "Choose left direction" << std::endl;
				isWatchingLeft = true;

                break;
            case 77: // Move right
                std::cout << "Choose right direction" << std::endl;
				isWatchingRight = true;

                break;
            }

			// Watch Player
            int newPosX = 0;
			int newPosY = 0;

            if (isWatchingUp)
            {
                newPosY = hero.getPosY() - 1;
				newPosX = hero.getPosX();
            }
			else if (isWatchingDown)
			{
				newPosY = hero.getPosY() + 1;
                newPosX = hero.getPosX();
			}
			else if (isWatchingLeft)
			{
				newPosX = hero.getPosX() - 1;
				newPosY = hero.getPosY();
			}
			else if (isWatchingRight)
			{
                newPosX = hero.getPosX() + 1;
                newPosY = hero.getPosY();
			}

            char symbol = dungeon.checkPosition(newPosX, newPosY);

            switch (symbol)
            {
            case '.':
				std::cout << "En attente de confirmation" << std::endl;

                if (_getch() == 13)
                {
                    hero.move(newPosX, newPosY);

					std::cout << "New Post : " << hero.getPosX() << " " << hero.getPosY() << std::endl;
                }
                else return;
				
                break;
            case '#':
				std::cout << "Case indisponible vous foncez dans le mur !" << std::endl;

				break;
            case 'S':
				std::cout << "Symbole : Spectre" << std::endl;
				break;
			case 'G':
				std::cout << "Symbole : Golem" << std::endl;
				break;
			case 'F':
				std::cout << "Symbole : Faucheur" << std::endl;
				break;
            default:
                std::cout << "Erreur symbole non detecte" << std::endl;
                break;
            }

            // Reset watching state
            isWatchingDown = false;
            isWatchingLeft = false;
            isWatchingRight = false;
            isWatchingUp = false;

            std::cout << "Press any key to continue..." << std::endl;
            std::cin.get(); // Pause
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
