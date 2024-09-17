#include "Entity.h"

Entity::Entity() : posX(0), posY(0), symbol('E'), life(100), power(50), movement(3) {}

Entity::~Entity() {}

bool Entity::isAlive()
{
	if (life > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Entity::setPos(std::vector<std::string> currentRoom)
{
    for (int line = 0; line < currentRoom.size(); line++)
    {
        for (int actualSymbol = 0; actualSymbol < currentRoom[line].size(); actualSymbol++)
        {
            if (currentRoom[line][actualSymbol] == symbol)
            {
                posX = actualSymbol;
                posY = line;
                return;
            }
        }
    }
}

void Entity::move(int x, int y)
{
	posX = x;
	posY = y;
}

void Entity::attack(Entity target)
{
	// Logic to attack target
}

int Entity::getPosX() const
{
	return posX;
}

int Entity::getPosY() const
{
	return posY;
}
