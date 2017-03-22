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
1. Playerʹ��u commandʹ��item.
2. ����Ѱ����u commandָ��λ���Ƿ���item����
	a.��ָ��λ����item, �����Playerû��item
	b.����item
		i.��PotionList/TreasureList��Ѱ��ָ��item
		ii.��ȡ���item
			1.�����item�޷���ʹ�ã������Player��item�޷�ʹ��
			2.�����item����ʹ�ã������item��effect��������Player
			  ������Ӧ��ֵ������item��List��ɾȥ



*/
