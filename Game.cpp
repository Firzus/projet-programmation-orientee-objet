#include "Game.h"

Game::Game()
{
    init();
    playTurn();
}

Game::~Game() {}

void Game::init()
{
    // - Initialize the dungeon
    getEntities();

    updateGame();
}

void Game::playTurn()
{
    while (!hero.isDead()) {
        // Reinitialiser les PM du heros au d�but du tour
        hero.resetMovement();

        // Tour du joueur
        playerTurn();

        // Tour des ennemis
        enemyTurn();
    }

    endGame();
}

void Game::endGame()
{
    // Affiche un message de fin de jeu temporaire
    infos.addInfo("Game Over !");
    updateGame();

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

void Game::updateGame()
{
    // Clear console
    system("cls");

    // Affichage de la room
    dungeon.updateRoom();

    // Affichage des infos
    infos.updateInfos(hero.getPower(), hero.getLife(), hero.getMovement());
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
                dungeon.updateSymbolAtPosition(posX, posY, dungeon.getEmptySpaceSymbol());
                dungeon.updateSymbolAtPosition(newPosX, newPosY, spectre.getSymbol());
                spectre.move(newPosX, newPosY);
            }
        }
        break;
    }
    case 'G': {
        for (Golem& golem : golems) {
            if (golem.getPosX() == posX && golem.getPosY() == posY) {
                dungeon.updateSymbolAtPosition(posX, posY, dungeon.getEmptySpaceSymbol());
                dungeon.updateSymbolAtPosition(newPosX, newPosY, golem.getSymbol());
                golem.move(newPosX, newPosY);
            }
        }
        break;
    }
    case 'F': {
        for (Faucheur& faucheur : faucheurs) {
            if (faucheur.getPosX() == posX && faucheur.getPosY() == posY) {
                dungeon.updateSymbolAtPosition(posX, posY, dungeon.getEmptySpaceSymbol());
                dungeon.updateSymbolAtPosition(newPosX, newPosY, faucheur.getSymbol());
                faucheur.move(newPosX, newPosY);
            }
        }
        break;
    }
    case '@': {
        dungeon.updateSymbolAtPosition(posX, posY, dungeon.getEmptySpaceSymbol());
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
    dungeon.updateSymbolAtPosition(newPosX, newPosY, dungeon.getEmptySpaceSymbol());

    // Special Enemy Skill
    char enemySymbol = ennemy->getSymbol();
    switch (enemySymbol)
    {
    case 'S':
        // Restaure les PV du h�ros
        hero.setLife(hero.getMaxLife());
        infos.addInfo("Le heros vient de restaurer ses points de vie");
        updateGame();
        break;
    case 'G':
        // + 20 Puissance au h�ros
        hero.buffPower(20);
        infos.addInfo("Le heros vient de gagner 20 points de puissance");
        updateGame();
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

        infos.addInfo("Tous les ennemis viennent de perdre 50 points de vie");
        updateGame();

        break;
    default:
        break;
    }

    if (!areEnemiesRemaining()) {
        std::cout << "Tous les ennemis ont ete vaincus !" << std::endl;

        // Go to the next room, get every entities, and reset player movement value
        dungeon.nextRoom();
        getEntities();
        hero.resetMovement();
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

void Game::playerTurn()
{
    infos.addInfo("Tour du joueur");
    updateGame();

    while (hero.getMovement() > 0) {
        infos.addInfo("Choose action: [Arrow keys] -> choose direction, [P] -> skip your turn");
        updateGame();

        // Demande une action au joueur
        char action = _getch();

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

            switch (symbol) {
            case ' ':
                infos.addInfo("[Enter] -> move");
                updateGame();
                dungeon.changeSelectedSymbolColor(newPosX, newPosY);

                if (_getch() == 13)
                {
                    updateEntityPosition(&hero, hero.getPosX(), hero.getPosY(), newPosX, newPosY);
                    hero.reduceMovement(1);
                }
                else return;

                break;
            case '#':
                infos.addInfo("Mur droit devant");
                updateGame();
                dungeon.changeSelectedSymbolColor(newPosX, newPosY);

                break;
            case 'S':
            case 'G':
            case 'F':
                infos.addInfo("[Enter] -> attack");
                updateGame();
                dungeon.changeSelectedSymbolColor(newPosX, newPosY);

                if (_getch() == 13)
                {
                    // Get the ennemy the hero point at
                    Entity* ennemy = getEntityAtPosition(newPosX, newPosY);

                    // Attack the ennemy
                    ennemy->takeDamage(hero.getPower());

                    infos.addInfo("Vous avez inflige " + std::to_string(hero.getPower()) + " a l'ennemi !");
                    updateGame();

                    // Remove the ennemy if dead
                    if (ennemy->isDead()) {
                        removeEnnemy(ennemy, newPosX, newPosY);

                        infos.addInfo("L'ennemi est mort !");
                        updateGame();
                    }
                    else {
                        infos.addInfo("L'ennemi a maintenant " + std::to_string(ennemy->getLife()) + " points de vie.");
                        updateGame();
                    }

                    // Sleep
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                else return;

                break;
            default:
                infos.addInfo("Erreur symbole non detecte");
                updateGame();
                break;
            }

            // Reset watching state
            isWatchingDown = false;
            isWatchingLeft = false;
            isWatchingRight = false;
            isWatchingUp = false;
        }
        else if (action == 112) 
        {
            // Skip player's turn
            infos.addInfo("You're skipping your turn.");

			return;
        }
        else {
            // - Invalid action
            infos.addInfo("Invalid action! Please try again.");
            updateGame();
        }

        updateGame();
    }
}

void Game::enemyTurn()
{
    infos.addInfo("Tour des ennemis");
    updateGame();

    // Parcourir tous les spectres
    for (Spectre& spectre : spectres) {
        if (spectre.isSkillReady())
        {
			while (spectre.getMovement() > 0)
			{
                moveAwayFromHero(spectre);

                updateGame();
			}

			// Reset skill cooldown
			spectre.resetSkillCooldown();
        }
        else
        {
            while (spectre.getMovement() > 0)
            {
                moveTowardsHero(spectre);

                updateGame();
            }

			// Update skill state
			spectre.updateSkillState();
        }

        spectre.resetMovement();
    }

    // Parcourir tous les golems
    for (Golem& golem : golems) {
        moveTowardsHero(golem);

        if (golem.isSkillReady())
        {
			// - Golem skill

            // Reset skill cooldown
            golem.resetSkillCooldown();
        }
        else {
            // Update skill state
            golem.updateSkillState();
        }
    }

    // Parcourir tous les faucheurs
    for (Faucheur& faucheur : faucheurs) {
        moveTowardsHero(faucheur);
    }

    updateGame();
}

void Game::moveTowardsHero(Entity& entity) {
    int heroX = hero.getPosX();
    int heroY = hero.getPosY();

    int entityX = entity.getPosX();
    int entityY = entity.getPosY();

    int deltaX = heroX - entityX;
    int deltaY = heroY - entityY;

    int newPosX = entityX;
    int newPosY = entityY;

    if (abs(deltaX) > abs(deltaY)) {
        newPosX += (deltaX > 0) ? 1 : -1;
    }
    else {
        newPosY += (deltaY > 0) ? 1 : -1;
    }

    char symbol = dungeon.checkPosition(newPosX, newPosY);
    if (symbol == ' ') {
        updateEntityPosition(&entity, entityX, entityY, newPosX, newPosY);
        entity.reduceMovement(1);
    }
    else if (symbol == '@') {
        hero.takeDamage(entity.getPower());
        infos.addInfo("Le Faucheur attaque le héros !");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Game::moveAwayFromHero(Entity& entity) {
    int heroX = hero.getPosX();
    int heroY = hero.getPosY();
    int entityX = entity.getPosX();
    int entityY = entity.getPosY();

    int deltaX = entityX - heroX;
    int deltaY = entityY - heroY;

    int newPosX = entityX;
    int newPosY = entityY;

    if (abs(deltaX) > abs(deltaY)) {
        newPosX += (deltaX > 0) ? 1 : -1;
    }
    else {
        newPosY += (deltaY > 0) ? 1 : -1;
    }

    char symbol = dungeon.checkPosition(newPosX, newPosY);
    if (symbol == ' ') {
        updateEntityPosition(&entity, entityX, entityY, newPosX, newPosY);
        entity.reduceMovement(1);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
