#pragma once

#include <vector>
#include <string>

class Entity
{
protected:
	int posX;
	int posY;
	char symbol;
	int life;
	int power;
	int movement;

public:
	Entity();
	~Entity();

	bool isAlive() const;
	void move(int x, int y);
	void attack(Entity target);
	void takeDamage(int damage);
	int getPosX() const;
	int getPosY() const;
};