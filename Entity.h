#pragma once

#include <vector>
#include <string>
#include <thread>
#include <chrono>

class Entity
{
protected:
	int posX;
	int posY;
	char symbol;
	std::string name;
	int maxLife;
	int life;
	int power;
	int movement;
	int maxMovement;
	int skillCooldown;
	int maxSkillCooldown;
	bool hasAttacked;

public:
	Entity();
	~Entity();

	void init();
	bool isDead() const;
	void move(int x, int y);
	virtual void takeDamage(int damage);
	void buffPower(int powerBuff);
	bool isSkillReady() const;
	void resetSkillCooldown();
	void updateSkillState();
	virtual void attack(Entity& target);

	// Getters and setters
	int getPower() const { return power; }

	int getLife() const { return life; }
	void setLife(int newLife) { life = newLife; }

	int getMaxLife() const { return maxLife; }

	char getSymbol() const { return symbol; }

	std::string getName() const { return name; }

	int getPosX() const { return posX; }
	int getPosY() const { return posY; }

	int getMovement() const { return movement; }
	void reduceMovement(int amount) { movement -= amount; }
	void boostMovement(int amount) { movement += amount; }
	void resetMovement() { movement = maxMovement; }

	int getMaxMovement() const { return maxMovement; }

	void setHasAttacked(bool attacked) { hasAttacked = attacked; }
	bool getHasAttacked() const { return hasAttacked; }
};