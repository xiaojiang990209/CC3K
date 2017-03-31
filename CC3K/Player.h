#pragma once
#include"Character.h"

class Player : public Character
{
private:
	bool attackedMerchant;
	int gold;
	int score;
protected:
	virtual bool attackPlayer(int x, int y);
	virtual void move(int x, int y);
public:
	Player(int x, int y, std::string type, int hp, int atk, int def);
	int getGold();
	int getScore();
	void setGold(int gold);
	void update();
};

class Knight :public Player
{
public:
	Knight(int x, int y);
	void update();
};

class Wizard :public Player
{
public:
	Wizard(int x, int y);
	void update();
};

class Samurai :public Player
{
public:
	Samurai(int x, int y);
	void update();
};