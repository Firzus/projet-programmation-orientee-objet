#include "Golem.h"

Golem::Golem()
{
	name = "Golem";
	symbol = 'G';
	life = 150;
	maxLife = 150;
	power = 50;
	maxMovement = 3;
	skillCooldown = 2;
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