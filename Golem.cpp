#include "Golem.h"

Golem::Golem()
{
	symbol = 'G';
	life = 150;
	maxLife = 150;
	power = 50;
	maxMovement = 3;
	// TODO : Set the skill cooldown range
	skillCooldown = 0; // 2
	maxSkillCooldown = 4;
}

Golem::~Golem() {}

void Golem::takeDamage(int damage)
{
	if (Entity::isSkillReady())
	{
		damage = 0;
	}

	Entity::takeDamage(damage);
}
