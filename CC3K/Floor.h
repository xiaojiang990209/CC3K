#pragma once
#include"Entity.h"
#include"Chamber.h"
#include"Player.h"
#include"Enemy.h"
#include<vector>
#include<string>

class Floor
{
private:
	static Floor *f;
	Player *p;
	std::vector<std::string> defaultMap;
	std::vector<std::string> map;
	std::vector<Chamber*> chamberList;
	int level;
	Entity *stair;
	Floor();
	
	void randomizeObjectLocation(int &x, int &y, Chamber *&c);
	void spawnPlayer();
	void spawnStairs();
	void generatePotion(int potionIndex);
	void generateDragonHoard();
	void generateGoldPile();
	void generateEnemy(int enemyIndex);
	void generateFloor();
public:
	static Floor* getInstance();
	Player* getPlayer();
	void setPlayer(Player *p);
	int getLevel();
	void initMap(std::vector<std::string> map);
	std::vector<std::string>& getMap();
	void restoreMapFromCoordinate(int x, int y);
	Character* getEnemyFromCoordinate(int x, int y);
	Potion* getPotionFromCoordinate(int x, int y);
	Treasure* getTreasureFromCoordinate(int x, int y);
	void outputFloor();
	void initFloor();
	void update();
};