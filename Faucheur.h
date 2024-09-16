#pragma once

#include "Entity.h"
#include "Monster.h"

class Faucheur : public Entity, public Monster
{
	void skill();
	void reward();
public:
	Faucheur();
	~Faucheur();
};

