#pragma once

#include "Entity.h"
#include "Monster.h"

class Golem : public Entity, public Monster
{
	void skill();
	void reward();

public:
	Golem();
	~Golem();
};