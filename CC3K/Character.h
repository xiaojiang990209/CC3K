#pragma once
#include"Entity.h"
class Character : public Entity {
private:
	int iniHp;
	int hp;
	int atk;
	int def;
	int curFloorAtkBoost;
	int curFloorDefBoost;
	bool isDead;
	
public:
	Character(int x, int y, char display, std::string type, int hp, int atk, int def);
	int getHP();
	int getATK();
	int getDEF();
	void changeHP(int hp);
	void changeCurFloorATKBoost(int atkBoost);
	void changeCurFloorDEFBoost(int defBoost);
	void restoreCurFloorBoost();
	bool getIsDead();
	virtual void combat(Character *enemy);
	virtual void move();

};