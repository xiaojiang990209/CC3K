#pragma once
#include"Entity.h"
#include"Character.h"
#include"Potion.h"
#include"Treasure.h"
#include<vector>
#include<map>

class Chamber:public Entity
{
private:
	std::vector<Character*> characterList;
	std::vector<Potion*> potionList;
	std::vector<Treasure*> treasureList;
	std::map<int, std::pair<int, int> > xBoundaries;
	int length;
	int width;
	bool hasPlayer;
	bool hasStairs;
	void updateCharacterList();
	void updatePotionList();
	void updateTreasureList();
public:
	Chamber(int x, int y, int length, int width);
	void addCharacter(Character *c);
	void addPotion(Potion *p);
	void addTreasure(Treasure *t);
	void updateChamber();
	int getLength();
	int getWidth();
	void setHasPlayer(bool hasPlayer);
	void setHasStairs(bool hasStairs);
	bool isInChamber(int x, int y);
	bool getHasPlayer();
	bool getHasStairs();
	Character* getCharacter(int x, int y);
	Potion* getPotion(int x, int y);
	Treasure* getTreasure(int x, int y);
};