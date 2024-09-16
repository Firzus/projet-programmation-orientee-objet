#pragma once

#include "Entity.h"
#include "Monster.h"

class Spectre : public Entity, public Monster
{
	void skill();
	void reward();

public:
	Spectre();
	~Spectre();
};

