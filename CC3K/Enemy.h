#pragma once
#include"Character.h"
#include"Item.h"
class Enemy : public Character
{
protected:
	bool findEnemy(int x, int y);
	bool findPotion(int x, int y);
	virtual bool attackPlayer();
	virtual bool drinkPotion();
	virtual void moveRandomly();
public:
	Enemy(int x, int y, char display, std::string type, int hp, int atk, int def);
};

class GridBug :public Enemy
{
private:
	bool attackPlayer();
	void moveRandomly();

public:
	GridBug(int x, int y);
	void update();
};

class Goblin : public Enemy
{
public:
	Goblin(int x, int y);
	void update();
};