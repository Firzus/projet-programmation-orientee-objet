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

	void move(int x, int y);
	void attack(Entity target);

public:
	Entity();
	~Entity();

	bool isAlive();
	void setPos(std::vector<std::string> currentRoom);
	int getPosX() const;
	int getPosY() const;
};