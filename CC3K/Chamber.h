#pragma once
#include"Character.h"
#include"Entity.h"

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
	void initXBoundaries(int chamberIndex);
public:
	Chamber(int x, int y, int length, int width, int chamberIndex);
	void initChamber();
	void addCharacter(Character *c);
	void addPotion(Potion *p);
	void addTreasure(Treasure *t);
	bool isInChamber(int x, int y);
	int getLength();
	int getWidth();
	bool getHasPlayer();
	bool getHasStairs();
	void setHasPlayer(bool hasPlayer);
	void setHasStairs(bool hasStairs);
	Character* getCharacter(int x, int y);
	Potion* getPotion(int x, int y);
	Treasure* getTreasure(int x, int y);
	void updateChamber();

};