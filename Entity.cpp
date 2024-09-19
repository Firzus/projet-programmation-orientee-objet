#include "Entity.h"

Entity::Entity() {}

Entity::~Entity() {}

bool Entity::isDead() const 
{
	if (life <= 0)
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

void Entity::takeDamage(int damage)
{
	life -= damage;
	life < 0 ? life = 0 : life;
}

void Entity::buffPower(int powerBuff)
{
	power += powerBuff;
}

bool Entity::isSkillReady() const
{
	if (skillCooldown == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Entity::resetSkillCooldown()
{
	skillCooldown = maxSkillCooldown;
}

void Entity::updateSkillState()
{
	if (skillCooldown > 0)
	{
		skillCooldown--;
	}
}
