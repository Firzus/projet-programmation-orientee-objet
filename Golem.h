#pragma once

#include "Entity.h"

class Golem : public Entity
{
public:
	Golem();
	~Golem();

	void takeDamage(int damage) override;
};