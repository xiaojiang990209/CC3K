#pragma once
#include"Entity.h"
#include"Chamber.h"
#include"Player.h"
#include<vector>
#include<string>

class Floor
{
private:
	Floor *f;
	Player *p;
	std::vector<std::string> initMap;
	std::vector<std::string> map;
	std::vector<Chamber*> chambers;
	int level;
	Entity *stair;
	Floor();
	void spawnPlayer();
	void spawnStairs();
	void generateFloor();
public:
	static Floor* getInstance();
	void outputFloor();
	Player* getPlayer();
	void initMap(std::vector<std::string> map);
	std::vector<std::string>& getMap();
	Character* getEnemyFromCoordinate(int x, int y);
	Potion* getPotionFromCoordinate(int x, int y);
	Treasure* getTreasureFromCoordinate(int x, int y);
};