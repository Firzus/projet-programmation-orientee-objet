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
	void takeDamage(int damage);
	int returnPower();
	void setPos(std::vector<std::string> currentRoom);
	int getPosX() const;
	int getPosY() const;
};