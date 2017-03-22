#include "Potion.h"

Potion::Potion(int x, int y, std::string type, int hpEffect, int atkEffect, int defEffect, bool isPositive):Item(x,y,'!',type)
{
	this->hpEffect = hpEffect;
	this->atkEffect = atkEffect;
	this->defEffect = defEffect;
	this->isPositive = isPositive;
}

void Potion::effect(Character *c)
{
	c->changeHP(this->hpEffect);
	c->changeCurFloorATKBoost(this->atkEffect);
	c->changeCurFloorDEFBoost(this->defEffect);
}

RestoreHealthPotion::RestoreHealthPotion(int x, int y) :Potion(x, y, "RestoreHealth", 30, 0, 0, true)
{

}

BoostAtkPotion::BoostAtkPotion(int x, int y) : Potion(x, y, "BoostAtk", 0, 10, 0, true)
{

}

BoostDefPotion::BoostDefPotion(int x, int y) : Potion(x, y, "BoostDef", 0, 0, 10, true)
{

}

PoisonHealthPotion::PoisonHealthPotion(int x, int y) : Potion(x, y, "PoisonHealth", -15, 0, 0, false)
{

}

WoundAtkPotion::WoundAtkPotion(int x, int y) : Potion(x, y, "WoundAtk", 0, -5, 0, false)
{

}

WoundDefPotion::WoundDefPotion(int x, int y) : Potion(x, y, "WoundDef", 0, 0, -5, false)
{

}

/*
1. Player使用u command使用item.
2. 程序寻找在u command指定位置是否有item可用
	a.若指定位置无item, 则告诉Player没有item
	b.若有item
		i.在PotionList/TreasureList中寻找指定item
		ii.获取这个item
			1.如果该item无法被使用，则告诉Player该item无法使用
			2.如果该item可以使用，则调用item的effect方法，给Player
			  加上相应数值，并把item从List中删去



*/
