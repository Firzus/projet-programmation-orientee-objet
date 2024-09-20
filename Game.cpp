#include "Game.h"

Game::Game()
{
    init();
}

Game::~Game() {}

void Game::init()
{
	isPlaying = true;

	dungeon.init();
    hero.init();
	spectres.clear();
	faucheurs.clear();
	golems.clear();

    getEntities();

    for (Spectre& spectre : spectres) {
        spectre.init();
    }
    for (Golem& golem : golems) {
        golem.init();
    }
    for (Faucheur& faucheur : faucheurs) {
		faucheur.init();
    }

    updateGame();

    playTurn();
}

void Game::playTurn()
{
    while (!hero.isDead()) {
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
    infos.addInfo("Game Over !", 4);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    init();;
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
    dungeon.updateRoom(hero.getPosX(), hero.getPosY(), hero.getMovement());

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
        infos.addInfo("Le heros vient de restaurer ses points de vie", 10);
        updateGame();
        break;
    case 'G':
        // + 20 Puissance au h�ros
        hero.buffPower(20);
        infos.addInfo("Le heros vient de gagner 20 points de puissance", 12);
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

        infos.addInfo("Tous les ennemis viennent de perdre 50 points de vie", 6);
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
    infos.addInfo("Tour du Joueur", 9);
    updateGame();

    hero.resetMovement();

    while (hero.getMovement() > 0) {
        infos.addInfo("Choose action:\nSelect direction [Arrow keys]\nSkip your turn            [P]", 7);
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
                infos.addInfo("[Enter] -> move", 7);
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
                infos.addInfo("Mur droit devant", 7);
                updateGame();
                dungeon.changeSelectedSymbolColor(newPosX, newPosY);

                break;
            case 'S':
            case 'G':
            case 'F':
                infos.addInfo("[Enter] -> attack", 7);
                updateGame();
                dungeon.changeSelectedSymbolColor(newPosX, newPosY);

                if (_getch() == 13)
                {
                    // Get the ennemy the hero point at
                    Entity* ennemy = getEntityAtPosition(newPosX, newPosY);

                    // Attack the ennemy
                    ennemy->takeDamage(hero.getPower());

                    infos.addInfo("Vous avez inflige " + std::to_string(hero.getPower()) + " a l'ennemi !", 6);
                    updateGame();

                    // Remove the ennemy if dead
                    if (ennemy->isDead()) {
                        removeEnnemy(ennemy, newPosX, newPosY);

                        infos.addInfo("L'ennemi est mort !", 7);
                        updateGame();
                    }
                    else {
                        infos.addInfo("L'ennemi a maintenant " + std::to_string(ennemy->getLife()) + " points de vie.", 7);
                        updateGame();
                    }

                    // Sleep
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                else return;

                break;
            default:
                infos.addInfo("Erreur symbole non detecte", 7);
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
            infos.addInfo("You're skipping your turn.", 7);

			return;
        }
        else {
            // - Invalid action
            infos.addInfo("Invalid action! Please try again.", 7);
            updateGame();
        }

        updateGame();
    }
}

void Game::enemyTurn()
{
    infos.addInfo("Tour des ennemis", 4);
    updateGame();

    // Parcourir tous les spectres
    for (Spectre& spectre : spectres) {

        spectre.resetMovement();

        // Skill
        if (spectre.isSkillReady())
        {
            // - Faucheur skill
			int boostAmount = 3;
            spectre.boostMovement(boostAmount);

            infos.addInfo(spectre.getName() + " : + " + std::to_string(boostAmount) + "PM", 4);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            updateGame();

            // Reset skill cooldown
            spectre.resetSkillCooldown();
        }
        else {
            // Update skill state
            spectre.updateSkillState();
        }

        // Movement
        while (spectre.getMovement() > 0 && !isHeroInRange(spectre))
        {
            moveTowardsHero(spectre);

            updateGame();
        }

        // Attack
        if (isHeroInRange(spectre) && !spectre.getHasAttacked()) {
            infos.addInfo("Le " + spectre.getName() + " vous a inflige " + std::to_string(spectre.getPower()) + " dommages", 4);

            spectre.attack(hero);
            spectre.setHasAttacked(true);

            updateGame();
        }
    }

    // Parcourir tous les golems
    for (Golem& golem : golems) {

        golem.resetMovement();

        // Skill
        if (golem.isSkillReady())
        {
            // Golem skill
            infos.addInfo("Golem : Immunise au prochain coup", 4);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            updateGame();

            golem.resetSkillCooldown();
        }
        else {
            golem.updateSkillState();
        }

        // Movement
        while (golem.getMovement() > 0 && !isHeroInRange(golem))
        {
            moveTowardsHero(golem);
          
            updateGame();
        }

        // Attack
        if (isHeroInRange(golem) && !golem.getHasAttacked()) 
        {
            infos.addInfo("Le Golem vous a inflige " + std::to_string(golem.getPower()) + " dommages", 4);

            golem.attack(hero);
            golem.setHasAttacked(true);

            updateGame();
        }
    }

    // Parcourir tous les faucheurs
    for (Faucheur& faucheur : faucheurs) {

        faucheur.resetMovement();

        if (static_cast<double>(faucheur.getLife()) / faucheur.getMaxLife() <= 0.5)
        {
			// Skill
            while (faucheur.getMovement() > 0)
            {
                moveAwayFromHero(faucheur);
                updateGame();
            }
        }
        else
        {
            // Movement
            while (faucheur.getMovement() > 0 && !isHeroInRange(faucheur))
            {
                moveTowardsHero(faucheur);
                updateGame();
            }
        }

        // Attack
        if (isHeroInRange(faucheur) && !faucheur.getHasAttacked()) {
            infos.addInfo("Le " + faucheur.getName() + " vous a inflige " + std::to_string(faucheur.getPower()) + " dommages", 4);

            faucheur.attack(hero);
            faucheur.setHasAttacked(true);

            updateGame();
        }
    }

	resetEnemyAttackFlags();
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
    else
    {
		entity.reduceMovement(1);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

bool Game::isHeroInRange(const Entity& enemy) const {
    int distanceX = abs(hero.getPosX() - enemy.getPosX());
    int distanceY = abs(hero.getPosY() - enemy.getPosY());
    return (distanceX == 1 && distanceY == 0) || (distanceX == 0 && distanceY == 1);
}

void Game::resetEnemyAttackFlags() {
    for (Spectre& spectre : spectres) {
        spectre.setHasAttacked(false);
    }
    for (Golem& golem : golems) {
        golem.setHasAttacked(false);
    }
    for (Faucheur& faucheur : faucheurs) {
        faucheur.setHasAttacked(false);
    }
}
