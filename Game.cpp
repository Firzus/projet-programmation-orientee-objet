#include "Game.h"

Game::Game()
{
	std::cout << "Game started" << std::endl;

	init();
}

Game::~Game(){}

void Game::init()
{
	// Initialization game
    dungeon.loadRoom();

    // affiche la map actuelle
	for (std::string line : dungeon.getCurrentRoom()) {
		std::cout << line << std::endl;
	}

	// then -> play the game
}

void Game::playTurn()
{
	// Turn logic

	isPlaying = true;

    while (isPlaying) { // && hero.isAlive()
        // 1. Clear Screen in map class

        // 2. Affiche l'état actuel du jeu

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
        case 'p':
            isPlaying = false;
            break;
        default:
            std::cout << "Invalid action! Please try again." << std::endl;
            break;
        }

        // Si le monstre est toujours en vie, il réagit
		if (true) { // monster.isAlive() == true
            // 1. Le monstre se déplace vers le héros
			if (true) { // Si le monstre est adjacent au héros
                // Le monstre attaque s'il est adjacent au héros
            }
        }

        // Si le héros est mort, le jeu se termine
		if (true) { // hero.isAlive() == false
            std::cout << "Game Over! The hero has fallen." << std::endl;
            isPlaying = false;
        }
    }

	endGame();
}

void Game::endGame()
{    
	// Recommence le jeu en retournant à la première salle

	// Affiche un message de fin de jeu temporaire
	std::cout << "End Game" << std::endl;

    init();
}
