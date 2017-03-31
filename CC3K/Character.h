#pragma once
#include"Entity.h"
#include"Floor.h"
class Character : public Entity {
private:
	int iniHp;
	int hp;
	int atk;
	int def;
	int curFloorAtkBoost;
	int curFloorDefBoost;
	bool isDead;
	Floor *f;

protected:
	void combat(Character *enemy);
	void changeHP(int hp);
	void changeCurFloorATKBoost(int atkBoost);
	void changeCurFloorDEFBoost(int defBoost);
	void restoreCurFloorBoost();
public:
	Character(int x, int y, char display, std::string type, int hp, int atk, int def);
	int getHP();
	int getATK();
	int getDEF();
	bool getIsDead();
	void setIsDead(bool isDead);
	void usePotion(Potion *p);
	Floor* getFloor();
	virtual void update();

};