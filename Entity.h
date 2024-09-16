#pragma once

class Entity
{
	// attributs
	int posX;
	int posY;

	char symbol;
	int life;
	int power;
	int movement;

public:
	Entity();
	~Entity();
	void move(int x, int y);
	void attack(Entity target);
};

