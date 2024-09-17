#include "Entity.h"

Entity::Entity() : posX(0), posY(0), symbol('E'), life(100), power(50), movement(3) {}

Entity::~Entity() {}

bool Entity::isAlive() const 
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

void Entity::move(int x, int y)
{
	posX = x;
	posY = y;
}

// Logic to attack target
void Entity::takeDamage(int damage)
{
	// Do damages
	if (life >= damage)
	{
		life -= damage;
	}
	else
	{
		life == 0;
	}

	// Check if entity is still alive
	isAlive();
}

int Entity::returnPower()
{
	return power;
}

void Entity::takeDamage(int damage)
{
	life -= damage;
	life < 0 ? life = 0 : life;
}

int Entity::getPosX() const
{
	return posX;
}

int Entity::getPosY() const
{
	return posY;
}
