#include "Entity.h"

Entity::Entity() : posX(0), posY(0), symbol('E'), life(100), power(50), movement(3) {}

Entity::~Entity() {}

void Entity::move(int x, int y)
{
	posX += x;
	posY += y;
}

void Entity::attack(Entity target)
{
	// Logic to attack target
}
