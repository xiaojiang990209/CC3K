#pragma once
#include"Item.h"
#include"Character.h"
class Potion :public Item
{
private:
	int hpEffect;
	int atkEffect;
	int defEffect;
	bool isPositive;
public:
	Potion(int x, int y, std::string type, int hpEffect, int atkEffect, int defEffect, bool isPositive);
	int getHpEffect();
	int getAtkEffect();
	int getDefEffect();
};

class RestoreHealthPotion: public Potion
{
public:
	RestoreHealthPotion(int x, int y);
};

class BoostAtkPotion : public Potion
{
public:
	BoostAtkPotion(int x, int y);
};

class BoostDefPotion : public Potion
{
public:
	BoostDefPotion(int x, int y);
};

class PoisonHealthPotion : public Potion
{
public:
	PoisonHealthPotion(int x, int y);
};

class WoundAtkPotion :public Potion
{
public:
	WoundAtkPotion(int x, int y);
};

class WoundDefPotion :public Potion
{
public:
	WoundDefPotion(int x, int y);
};