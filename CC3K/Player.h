#pragma once
#include"Character.h"

class Player : public Character
{
private:
	bool isVisible;
	int gold;
	int score;
	void directionIntepreter(std::string dir, int &x, int &y);
protected:
	virtual bool attackPlayer(int x, int y);
	virtual bool drinkPotion(int x, int y);
	virtual bool collectGold(int x, int y);
	virtual bool move(int x, int y);
public:
	Player(int x, int y, std::string type, int hp, int atk, int def, bool isVisible);
	bool getIsVisible();
	void setIsVisible(bool isVisible);
	int getGold();
	int getScore();
	void setGold(int gold);
	void update();
};

class Knight :public Player
{
public:
	Knight(int x, int y);
};

/*
	Overrides the virtual function attackPlayer because of its special long range attack
*/
class Wizard :public Player
{
private:
	bool attackPlayer(int x, int y);
public:
	Wizard(int x, int y);
};

/*
	Overrides the virtual function attackPlayer because of its visibility
*/
class Samurai :public Player
{
public:
	Samurai(int x, int y);
};