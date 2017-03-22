#pragma once
#include"Character.h"

class Player : public Character
{
private:
	bool attackedMerchant;
	int gold;
	int score;
public:
	Player(int x, int y, std::string type, int hp, int atk, int def);
	int getGold();
	int getScore();
	void setGold(int gold);
};

class Knight :public Player
{
public:
	Knight(int x, int y);
};