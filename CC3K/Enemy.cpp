#include "Enemy.h"

Enemy::Enemy(int x, int y, char display, std::string type, int hp, int atk, int def, Item *item, bool hasItem):Character(x,y,display,type, hp, atk, def)
{
	this->item = item;
	this->hasItem = hasItem;
}
