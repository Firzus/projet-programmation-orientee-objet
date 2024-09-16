#include "Game.h"

Game::Game()
{
	init();
}

Game::~Game(){}

void Game::init()
{
	// Initialization game

	// then -> play the game
}

void Game::playTurn()
{
	// Turn logic

	isPlaying = true;

    while (isPlaying) { // && hero.isAlive()
        // 1. Clear Screen in map class

        // 2. Affiche l'�tat actuel du jeu

        // 3. Demande une action au joueur

        char action;

        std::cout << "Choose action: (z/q/s/d) move, (enter), (q)uit: ";
        std::cin >> action;

        // Gestion des actions du joueur
        switch (action) {
        case 'z':
            // Move up
            break;
        case 's':
            // Move down
            break;
        case 'q':
            // Move left
            break;
        case 'd':
            // Move right
            break;
        case 'f':
			// Fight monster if adjacent else do nothing just moove

			// Si le dernier monstre du donjon est mort le jeu affiche un message de victoire
            break;
        case 'y':
            isPlaying = false;
            break;
        default:
            std::cout << "Invalid action! Please try again." << std::endl;
            break;
        }

        // Si le monstre est toujours en vie, il r�agit
		if (true) { // monster.isAlive() == true
            // 1. Le monstre se d�place vers le h�ros
			if (true) { // Si le monstre est adjacent au h�ros
                // Le monstre attaque s'il est adjacent au h�ros
            }
        }

        // Si le h�ros est mort, le jeu se termine
		if (true) { // hero.isAlive() == false
            std::cout << "Game Over! The hero has fallen." << std::endl;
            isPlaying = false;
        }
    }

	endGame();
}

void Game::endGame()
{    
	// Recommence le jeu en retournant � la premi�re salle

	// Affiche un message de fin de jeu temporaire
	std::cout << "End Game" << std::endl;

    init();
}
