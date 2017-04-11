#include"Character.h"
#include"TextPanel.h"
#include"Potion.h"
#include<cmath>
#include<iostream>

Character::Character(int x, int y, char display, std::string type, int hp, int atk, int def):Entity(x,y,display,type) 
{
	this->initHp = hp;
	this->hp = hp;
	this->atk = atk;
	this->def = def;
	this->curFloorAtkBoost = 0;
	this->curFloorDefBoost = 0;
	this->isDead = false;
}

void Character::changeHP(int hp)
{
	//If the hp after is greater than the initial hp, then
	//the hp is the initial hp
	if (this->hp + hp > this->initHp)
	{
		this->hp = this->initHp;
	}
	//else treat it the normal way
	else
	{
		this->hp += hp;
	}
}

void Character::changeCurFloorATKBoost(int atkBoost)
{
	this->curFloorAtkBoost += atkBoost;
}

void Character::changeCurFloorDEFBoost(int defBoost)
{
	this->curFloorDefBoost += defBoost;
}

void Character::restoreCurFloorBoost()
{
	this->curFloorAtkBoost = 0;
	this->curFloorDefBoost = 0;
}

void Character::combat(Character *enemy)
{
	//检测对象
	//如果攻击对象（this）是Player，则主语为you
	//否则，被攻击对象为Player，主语为攻击对象（enemy）的类型

	int damage = -ceil(this->getATK()*(100.0 - enemy->getDEF()) / 100.0);
	enemy->changeHP(damage);
	if (enemy->getHP() <= 0)
	{
		enemy->setIsDead(true);
	}
	//若攻击对象的display:char 为‘@’，则代表攻击对象为Player
	if (this->getDisplay() == '@')
	{
		TextPanel::appendMessage("You attack the " + enemy->getType() + " for " + std::to_string(-damage) + "damage!\n");
	}
	//否则，更换主语为Enemy的类型，宾语为You（player）
	else
	{
		TextPanel::appendMessage(this->getType() + " attacks you for " + std::to_string(-damage) + " damage!\n");
	}
}

int Character::getHP()
{
	return this->hp;
}

int Character::getInitHp()
{
	return this->initHp;
}

int Character::getATK()
{
	return this->atk+this->curFloorAtkBoost;
}

int Character::getDEF()
{
	int defTotal = this->def + this->curFloorDefBoost;
	if (defTotal > 100) {
		return 100;
	}
	else if(defTotal<0)
	{
		return 0;
	}
	else
	{
		return defTotal;
	}
}

void Character::setIsDead(bool isDead)
{
	this->isDead = isDead;
}

bool Character::getIsDead()
{
	return this->isDead;
}

void Character::usePotion(Potion *p)
{
	p->setIsUsed(true);
	this->changeCurFloorATKBoost(p->getAtkEffect());
	this->changeCurFloorDEFBoost(p->getDefEffect());
	this->changeHP(p->getHpEffect());
}

void Character::update()
{

}