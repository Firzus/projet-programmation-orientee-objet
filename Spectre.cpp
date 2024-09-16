#include "Spectre.h"

Spectre::Spectre()
{
	posX = 0;
	posY = 0;
	symbol = 'S';
	life = 50;
	power = 25;
	movement = 2;
}

Spectre::~Spectre() {}

void Spectre::skill()
{
	// IA Fuyard
}

void Spectre::reward()
{
	// Restaure les PV du héros
}