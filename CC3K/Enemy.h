#pragma once
#include"Character.h"
#include"Item.h"
class Enemy : public Character
{
private:
	Item *item;
	bool hasItem;
public:
	Enemy(int x, int y, char display, std::string type, int hp, int atk, int def, Item *item, bool hasItem);
	void dropItem();
};