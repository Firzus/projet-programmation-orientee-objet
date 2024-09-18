#include "Game.h"

Game::Game()
{
	init();
    playTurn();
}

Game::~Game(){}

void Game::init()
{
	// - Initialize the dungeon
    getEntities();

    dungeon.updateGame();
}

void Game::playTurn()
{
    isPlaying = true;

    while (isPlaying && !hero.isDead()) {
        // R�initialiser les PM du h�ros au d�but du tour
        hero.resetMovement();

        while (hero.getMovement() > 0) {
            // Demande une action au joueur
            char action;

        std::cout << "Choose action: [Arrow keys] -> choose direction, [Enter] -> move / attack: ";
        action = _getch();

            // Gestion des actions du joueur
            if (action == -32) {
                action = _getch();
                switch (action) {
                case 72: // Watch up side
                    isWatchingUp = true;

                    break;
                case 80: // Watch down
                    isWatchingDown = true;

                    break;
                case 75: // Watch left side
                    isWatchingLeft = true;

                    break;
                case 77: // Watch right side
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

            dungeon.changeSymbolColor(newPosX, newPosY);

            switch (symbol) {
            case '.':
				std::cout << "En attente de confirmation de deplacement (enter)" << std::endl;

                    if (_getch() == 13)
                    {
						updateEntityPosition(&hero, hero.getPosX(), hero.getPosY(), newPosX, newPosY);
                        hero.reduceMovement(1);
                    }
                    else return;

                    break;
                case '#':
                    std::cout << "Case indisponible vous foncez dans le mur !" << std::endl;

                    break;
                case 'S':
                case 'G':
                case 'F':
                    std::cout << "Vous confirmez attaquer la cible ? (enter)" << std::endl;
                    if (_getch() == 13)
                    {
                        // Get the ennemy the hero point at
                        Entity* ennemy = getEntityAtPosition(newPosX, newPosY);

                        // Attack the ennemy
                        ennemy->takeDamage(hero.getPower());
                        std::cout << "Vous avez inflige " << hero.getPower() << " a l'ennemi !" << std::endl;

                        // Remove the ennemy if dead
                        if (ennemy->isDead()) {
                            removeEnnemy(ennemy, newPosX, newPosY);
                            std::cout << "L'ennemi est mort !" << std::endl;
                        }
                        else {
                            std::cout << "L'ennemi a maintenant " << ennemy->getLife() << " points de vie." << std::endl;
                        }

                        // Sleep
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }
                    else return;

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
            }
            else {
                // - Invalid action
                std::cout << "Invalid action! Please try again." << std::endl;
            }

            dungeon.updateGame();
        }

		// Tour des ennemis

        enemyTurn();
    }
}

void Game::endGame()
{    
	// Affiche un message de fin de jeu temporaire
	std::cout << "End Game" << std::endl;

    init();
    playTurn();
}

void Game::getEntities()
{
    for (int y = 0; y < dungeon.getCurrentRoom().size(); ++y) {
        for (int x = 0; x < dungeon.getCurrentRoom()[y].size(); ++x) {
            char symbol = dungeon.getCurrentRoom()[y][x];
            switch (symbol) {
            case '@':
                hero.move(x, y);
                break;
            case 'S': {
                Spectre spectre;
                spectre.move(x, y);
                spectres.push_back(spectre);
                break;
            }
            case 'G': {
                Golem golem;
                golem.move(x, y);
                golems.push_back(golem);
                break;
            }
            case 'F': {
                Faucheur faucheur;
                faucheur.move(x, y);
                faucheurs.push_back(faucheur);
                break;
            }
            default:
                break;
            }
        }
    }
}

Entity* Game::getEntityAtPosition(int x, int y)
{
    std::vector<std::string> currentRoom = dungeon.getCurrentRoom();

    for (int row = 0; row < currentRoom.size(); ++row) {
        for (int col = 0; col < currentRoom[row].size(); ++col) {
            if (row == y && col == x) {
                char symbol = currentRoom[row][col];
                switch (symbol) {
                case 'S': {
                    for (Spectre& spectre : spectres) {
                        if (spectre.getPosX() == x && spectre.getPosY() == y) {
                            return &spectre;
                        }
                    }
                    break;
                }
                case 'G': {
                    for (Golem& golem : golems) {
                        if (golem.getPosX() == x && golem.getPosY() == y) {
                            return &golem;
                        }
                    }
                    break;
                }
                case 'F': {
                    for (Faucheur& faucheur : faucheurs) {
                        if (faucheur.getPosX() == x && faucheur.getPosY() == y) {
                            return &faucheur;
                        }
                    }
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
    return nullptr;
}

void Game::updateEntityPosition(Entity* entity, int posX, int posY, int newPosX, int newPosY)
{
	char symbol = dungeon.getCurrentRoom()[posY][posX];

	switch (symbol) {
	case 'S': {
		for (Spectre& spectre : spectres) {
			if (spectre.getPosX() == posX && spectre.getPosY() == posY) {
				dungeon.updateSymbolAtPosition(posX, posY, '.');
				dungeon.updateSymbolAtPosition(newPosX, newPosY, spectre.getSymbol());
				spectre.move(newPosX, newPosY);
			}
		}
		break;
	}
	case 'G': {
		for (Golem& golem : golems) {
			if (golem.getPosX() == posX && golem.getPosY() == posY) {
				dungeon.updateSymbolAtPosition(posX, posY, '.');
				dungeon.updateSymbolAtPosition(newPosX, newPosY, golem.getSymbol());
				golem.move(newPosX, newPosY);
			}
		}
		break;
	}
	case 'F': {
		for (Faucheur& faucheur : faucheurs) {
			if (faucheur.getPosX() == posX && faucheur.getPosY() == posY) {
                dungeon.updateSymbolAtPosition(posX, posY, '.');
                dungeon.updateSymbolAtPosition(newPosX, newPosY, faucheur.getSymbol());
				faucheur.move(newPosX, newPosY);
			}
		}
		break;
	}
	case '@' : {
		dungeon.updateSymbolAtPosition(posX, posY, '.');
        dungeon.updateSymbolAtPosition(newPosX, newPosY, hero.getSymbol());
		hero.move(newPosX, newPosY);
		break;
	}
	default:
		break;
	}
}

void Game::removeEntityAtPosition(int x, int y)
{
    char symbol = dungeon.getCurrentRoom()[y][x];
    switch (symbol) {
    case 'S': {
        auto it = std::remove_if(spectres.begin(), spectres.end(), [x, y](Spectre& spectre) {
            return spectre.getPosX() == x && spectre.getPosY() == y;
            });
        spectres.erase(it, spectres.end());
        break;
    }
    case 'G': {
        auto it = std::remove_if(golems.begin(), golems.end(), [x, y](Golem& golem) {
            return golem.getPosX() == x && golem.getPosY() == y;
            });
        golems.erase(it, golems.end());
        break;
    }
    case 'F': {
        auto it = std::remove_if(faucheurs.begin(), faucheurs.end(), [x, y](Faucheur& faucheur) {
            return faucheur.getPosX() == x && faucheur.getPosY() == y;
            });
        faucheurs.erase(it, faucheurs.end());
        break;
    }
    default:
        break;
    }
}

void Game::removeEnnemy(Entity* ennemy, int newPosX, int newPosY)
{
    // 1. Remove the ennemy from the list
    removeEntityAtPosition(newPosX, newPosY);

    // 2. Remove the sylbol from the map
    dungeon.updateMapAfterEntityDeath(newPosX, newPosY);

    // Special Enemy Skill
    char enemySymbol = ennemy->getSymbol();
    switch (enemySymbol)
    {
    case 'S':
        // Restaure les PV du h�ros
        hero.setLife(hero.getMaxLife());
		dungeon.updateTextInfos("Le heros vient de restaurer ses points de vie");
        break;
    case 'G':
        // + 20 Puissance au h�ros
        hero.buffPower(20);
        dungeon.updateTextInfos("Le heros vient de gagner 20 points de puissance");
        break;
    case 'F':
        // -50 Points de vie � tout les monstres
        for (int y = 0; y < dungeon.getCurrentRoom().size(); ++y) {
            for (int x = 0; x < dungeon.getCurrentRoom()[y].size(); ++x) {
                char symbol = dungeon.getCurrentRoom()[y][x];
                if (symbol == 'S' || symbol == 'G' || symbol == 'F')
                {
                    Entity* ennemy = getEntityAtPosition(x, y);
                    ennemy->takeDamage(50);
                }
            }
        }

        dungeon.updateTextInfos("Tous les ennemis viennent de perdre 50 points de vie");

        break;
    default:
        break;
    }

    if (!areEnemiesRemaining()) {
        std::cout << "Tous les ennemis ont ete vaincus !" << std::endl;

		dungeon.nextRoom();
    }
}

bool Game::areEnemiesRemaining() {
    for (const auto& row : dungeon.getCurrentRoom()) {
        for (const auto& cell : row) {
            if (cell == 'S' || cell == 'G' || cell == 'F') {
                return true;
            }
        }
    }
    return false;
}

void Game::enemyTurn()
{
	// Parcourir tous les spectres
    for (Spectre& spectre : spectres) {
        if (!spectre.isDead()) {
            int newX = spectre.getPosX() + (rand() % 3 - 1); // -1, 0, ou 1
            int newY = spectre.getPosY() + (rand() % 3 - 1); // -1, 0, ou 1
            if (dungeon.checkPosition(newX, newY) == '.') {
                updateEntityPosition(&spectre, spectre.getPosX(), spectre.getPosY(), newX, newY);

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }

    // Parcourir tous les golems
    for (Golem& golem : golems) {
        if (!golem.isDead()) {
            // Exemple d'action : se d�placer al�atoirement
            int newX = golem.getPosX() + (rand() % 3 - 1); // -1, 0, ou 1
            int newY = golem.getPosY() + (rand() % 3 - 1); // -1, 0, ou 1
            if (dungeon.checkPosition(newX, newY) == '.') {
                updateEntityPosition(&golem, golem.getPosX(), golem.getPosY(), newX, newY);

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }

    // Parcourir tous les faucheurs
    for (Faucheur& faucheur : faucheurs) {
        if (!faucheur.isDead()) {
            // Exemple d'action : se d�placer al�atoirement
            int newX = faucheur.getPosX() + (rand() % 3 - 1); // -1, 0, ou 1
            int newY = faucheur.getPosY() + (rand() % 3 - 1); // -1, 0, ou 1
            if (dungeon.checkPosition(newX, newY) == '.') {
                updateEntityPosition(&faucheur, faucheur.getPosX(), faucheur.getPosY(), newX, newY);
          
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }

    dungeon.updateGame();
}