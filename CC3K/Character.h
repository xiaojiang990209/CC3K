#pragma once
#include"Entity.h"
class Potion;
class Character : public Entity {
private:
	int initHp;
	int hp;
	int atk;
	int def;
	int curFloorAtkBoost;
	int curFloorDefBoost;
	bool isDead;
protected:
	void combat(Character *enemy);
	void changeHP(int hp);
	void changeCurFloorATKBoost(int atkBoost);
	void changeCurFloorDEFBoost(int defBoost);
	
public:
	Character(int x, int y, char display, std::string type, int hp, int atk, int def);
	int getHP();
	int getInitHp();
	int getATK();
	int getDEF();
	bool getIsDead();
	void setIsDead(bool isDead);
	void usePotion(Potion *p);
	void restoreCurFloorBoost();
	virtual void update();

};