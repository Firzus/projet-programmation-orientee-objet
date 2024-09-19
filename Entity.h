#pragma once

#include <vector>
#include <string>

class Entity
{
protected:
	int posX;
	int posY;
	char symbol;
	int maxLife;
	int life;
	int power;
	int movement;
	int maxMovement;
	int skillCooldown;
	int maxSkillCooldown;

public:
	Entity();
	~Entity();

	bool isDead() const;
	void move(int x, int y);
	void takeDamage(int damage);
	void buffPower(int powerBuff);
	bool isSkillReady() const;
	void resetSkillCooldown();
	void updateSkillState();

	// Getters and setters
	int getPower() const { return power; }

	int getLife() const { return life; }
	void setLife(int newLife) { life = newLife; }

	int getMaxLife() const { return maxLife; }

	char getSymbol() const { return symbol; }

	int getPosX() const { return posX; }
	int getPosY() const { return posY; }

	int getMovement() const { return movement; }
	void reduceMovement(int amount) { movement -= amount; }
	void boostMovement(int amount) { movement += amount; }
	void resetMovement() { movement = maxMovement; }

	int getMaxMovement() const { return maxMovement; }
};