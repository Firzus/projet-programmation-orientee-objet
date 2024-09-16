#include "Golem.h"

Golem::Golem()
{
	posX = 0;
	posY = 0;
	symbol = 'G';
	life = 150;
	power = 50;
	movement = 3;
}

Golem::~Golem() {}

void Golem::skill()
{
	//Invu 1 tour / 4
}

void Golem::reward()
{
	// + 20 power to the hero
}
