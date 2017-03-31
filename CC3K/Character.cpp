#include"Character.h"
#include<cmath>

Character::Character(int x, int y, char display, std::string type, int hp, int atk, int def):Entity(x,y,display,type) 
{
	this->iniHp = hp;
	this->hp = hp;
	this->atk = atk;
	this->def = def;
	this->isDead = false;
}

void Character::changeHP(int hp)
{
	if (this->hp += hp > this->iniHp)
	{
		this->hp = this->iniHp;
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
	changeHP(-ceil(enemy->getATK()*(100.0-this->getDEF())/100.0));
	if (this->hp <= 0)
	{
		this->isDead = true;
	}
}

int Character::getHP()
{
	return this->hp;
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

Floor* Character::getFloor()
{
	return this->f;
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