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
	Player* p;
	std::vector<std::string> initMap;
	std::vector<std::string> map;
	std::vector<Chamber*> chambers;
	int level;
	Entity stair;
	Floor();
	void spawnPlayer();
	void spawnStairs();
	void generateFloor();
public:
	static Floor* getInstance();
	Player* getPlayer();
	std::vector<std::string>& getMap();
	Chamber* getChamberFromCoordinate(int x, int y);
};