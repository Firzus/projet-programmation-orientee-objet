#include "Faucheur.h"

Faucheur::Faucheur()
{
	posX = 0;
	posY = 0;
	symbol = 'F';
	life = 100;
	power = 75;
	movement = 4;
}

Faucheur::~Faucheur() {}

void Faucheur::skill()
{
	// IA CaC
}

void Faucheur::reward()
{
	// - 50 pdv to all the monsters
}