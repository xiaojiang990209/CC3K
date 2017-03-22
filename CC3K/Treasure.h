#pragma once
#include"Item.h"

class Treasure :public Item
{
private:
	int numGold;
public:
	Treasure(int x, int y, char display, std::string type, int numGold);
	int getNumGold();
};

class GoldPile :public Treasure
{
public:
	GoldPile(int x, int y);
};

//DragonHoard can inherit both Treasure and GoldPile
class DragonHoard :public Treasure
{
private:
	bool canBePickedUp;
public:
	DragonHoard(int x, int y);
	bool getCanBePickedUp();
	void setCanBePickedUp(bool canBePickedUp);
};

