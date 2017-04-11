#include"Floor.h"
#include"TextPanel.h"
#include<iostream>
#include<cstdlib>

using namespace std;

Floor *Floor::f;

Floor::Floor()
{
	this->chamberList.push_back(new Chamber(3, 3, 4, 26, 0));
	this->chamberList.push_back(new Chamber(39, 3, 10, 37, 1));
	this->chamberList.push_back(new Chamber(38, 10, 3, 12, 2));
	this->chamberList.push_back(new Chamber(4, 15, 7, 21, 3));
	this->chamberList.push_back(new Chamber(37, 16, 6, 39, 4));
	this->level = 0;
}

/*
	当游戏开始，需要把Floor类进行初始化
	或者：
	当当前一层结束，需要把Floor类所有东西全部重置
	把initFloor和restoreFloor/generateFloor分开写
*/
void Floor::initFloor()
{
	//delete all characters, potions and treasures
	for (Chamber *c : chamberList)
	{
		c->initChamber();
	}
	//restore map to default map
	this->map = this->defaultMap;
	//Ascend one level
	this->level++;
	//Restore player's last floor's boosts
	this->p->restoreCurFloorBoost();
	//Regenerate the floor
	this->generateFloor();
}

/*
	Generate the location of a non-stairs object
*/
void Floor::randomizeObjectLocation(int &x, int &y, Chamber *&c)
{
	x = 0, y = 0;
	c = nullptr;
	while (true)
	{
		//chamber = random 0 to 4, inclusive
		c = this->chamberList[rand() % 5];
		//square = random square in chamber, numbering left to right, top to bottom
		x = c->getX() + rand() % c->getWidth();
		y = c->getY() + rand() % c->getLength();
		//if square valid
		if (c->isInChamber(x, y) && this->map[y][x] == '.')
		{
			break;
		}

	}
}


/*
	spawnPlayer()未完成
*/
void Floor::spawnPlayer()
{
	//随机选择一个chamber
	int indexChamber = rand() % this->chamberList.size();
	Chamber *c = this->chamberList[indexChamber];
	//当选中的Chamber里有楼梯，重新选择
	while (c->getHasStairs())
	{
		indexChamber = rand() % this->chamberList.size();
		c = this->chamberList[indexChamber];
	}
	c->setHasPlayer(true);
	//随机生成x,y坐标
	int x = c->getX() + rand() % c->getWidth();
	int y = c->getY() + rand() % c->getLength();
	//当生成的(x,y)在chamber里，并且map的位置上是 '.' -> 未被占用 
	while (!c->isInChamber(x, y) || this->map[y][x] != '.')
	{
		x = c->getX() + rand() % c->getWidth();
		y = c->getY() + rand() % c->getLength();
	}
	this->p->setX(x);
	this->p->setY(y);
	this->map[y][x] = '@';

}

void Floor::spawnStairs()
{
	//随机选择一个chamber
	int indexChamber = rand() % this->chamberList.size();
	Chamber *c = this->chamberList[indexChamber];
	//当选中的Chamber里有Player，重新选择
	while (c->getHasPlayer())
	{
		indexChamber = rand() % this->chamberList.size();
		c = this->chamberList[indexChamber];
	}
	c->setHasStairs(true);
	//随机生成x,y坐标
	int x = c->getX() + rand() % c->getWidth();
	int y = c->getY() + rand() % c->getLength();
	//当生成的(x,y)在chamber里，并且map的位置上是 '.' -> 未被占用 
	while (!c->isInChamber(x, y) || this->map[y][x] != '.')
	{
		x = c->getX() + rand() % c->getWidth();
		y = c->getY() + rand() % c->getLength();
	}

	this->stair = new Entity(x, y, '>', "Stair");
	this->map[y][x] = '>';
}


/*
	Random generation of floors, according to the pseudocode outlined in the project.
*/
void Floor::generateFloor()
{
	this->spawnPlayer();
	this->spawnStairs();
	for (int i = 0; i<10; i++)
	{
		int potionIndex = rand() % 6;
		generatePotion(potionIndex);
	}
	for (int i = 0; i<10; i++)
	{
		int randomIndex = rand() % 8;
		if (randomIndex == 7)
		{
			generateDragonHoard();
		}
		else
		{
			generateGoldPile();
		}
	}
	for (int i = 0; i<20; i++)
	{
		int enemyIndex = rand() % 6;
		generateEnemy(enemyIndex);
	}
}

/*
generatePotion(int index)
1. randomize to get a chamber to put the Potion
2. while(true) to find the unoccupied and usable (x,y) coordinate
3. create that Potion from the index and add that to the chamber

*/
void Floor::generatePotion(int potionIndex)
{
	int x = 0, y = 0;
	Chamber *c = nullptr;
	this->randomizeObjectLocation(x, y, c);
	switch (potionIndex)
	{
	case 0:c->addPotion(new RestoreHealthPotion(x, y)); break;
	case 1:c->addPotion(new BoostAtkPotion(x, y)); break;
	case 2:c->addPotion(new BoostDefPotion(x, y)); break;
	case 3:c->addPotion(new PoisonHealthPotion(x, y)); break;
	case 4:c->addPotion(new WoundAtkPotion(x, y)); break;
	case 5:c->addPotion(new WoundDefPotion(x, y)); break;
	}
}

void Floor::generateDragonHoard()
{
	int x = 0, y = 0;
	Chamber *c = nullptr;
	this->randomizeObjectLocation(x, y, c);
	//Add dragonHoard to map
	c->addTreasure(new DragonHoard(x, y));
	//Create dragon alongside Dragon Hoard
	int dragonAddX = 0, dragonAddY = 0;
	while (true)
	{
		//Randomize addition factors to create random coordinate around the Dragon Hoard
		dragonAddX = -1 + rand() % 3;
		dragonAddY = -1 + rand() % 3;
		//If the coordinate of the Dragon Hoard itself is randomized, continue and keep randomizing
		if (dragonAddX == 0 && dragonAddY == 0) continue;
		//If the newly randomized coordinate is: 
		//	1. is in the Chamber itself, not out of bounds
		//	2. is available, namely the original coordinate should have a '.' on it.
		//If satisfied, break.
		if (c->isInChamber(x + dragonAddX, y + dragonAddY) && this->map[y + dragonAddY][x + dragonAddX] == '.')
		{
			break;
		}
	}
	//Add Dragon to accompany Dragon Hoard
	c->addCharacter(new Dragon(x + dragonAddX, y + dragonAddY));
}

void Floor::generateGoldPile()
{
	int x = 0, y = 0;
	Chamber *c = nullptr;
	this->randomizeObjectLocation(x, y, c);
	c->addTreasure(new GoldPile(x, y));
}

void Floor::generateEnemy(int enemyIndex)
{
	int x = 0, y = 0;
	Chamber *c = nullptr;
	this->randomizeObjectLocation(x, y, c);
	switch (enemyIndex)
	{
	case 0:
	case 1:c->addCharacter(new GridBug(x, y)); break;
	case 2:
	case 3:c->addCharacter(new Goblin(x, y)); break;
	case 4:c->addCharacter(new Orc(x, y)); break;
	case 5:c->addCharacter(new Merchant(x, y)); break;
	}
}

Floor* Floor::getInstance()
{
	if (f == nullptr)
	{
		f = new Floor();
	}
	return f;
}

void Floor::outputFloor()
{
	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[0].length(); j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

Player* Floor::getPlayer()
{
	return p;
}

void Floor::setPlayer(Player *p)
{
	this->p = p;
}

int Floor::getLevel()
{
	return this->level;
}

void Floor::initMap(std::vector<std::string> map)
{
	this->defaultMap = this->map = map;
}

std::vector<std::string>& Floor::getMap()
{
	return map;
}

void Floor::restoreMapFromCoordinate(int x, int y)
{
	this->map[y][x] = this->defaultMap[y][x];
}

Character* Floor::getEnemyFromCoordinate(int x, int y)
{
	Chamber *chamber = nullptr;
	for (Chamber *c : this->chamberList)
	{
		if (c->isInChamber(x, y))
		{
			chamber = c;
			break;
		}
	}
	return chamber->getCharacter(x, y);
}

Potion* Floor::getPotionFromCoordinate(int x, int y)
{
	Chamber *chamber = nullptr;
	for (Chamber *c : this->chamberList)
	{
		if (c->isInChamber(x, y))
		{
			chamber = c;
			break;
		}
	}
	return chamber->getPotion(x, y);
}

Treasure* Floor::getTreasureFromCoordinate(int x, int y)
{
	Chamber *chamber = nullptr;
	for (Chamber *c : this->chamberList)
	{
		if (c->isInChamber(x, y))
		{
			chamber = c;
			break;
		}
	}
	return chamber->getTreasure(x, y);
}

void Floor::update()
{
	//如果Player已经到达当前楼层的楼梯了
	if (p->getX() == stair->getX() && p->getY() == stair->getY())
	{
		this->initFloor();
	}
	this->outputFloor();
	TextPanel::outputStates();
	p->update();
	for (Chamber *c : chamberList)
	{
		c->updateChamber();
	}
	TextPanel::outputMessage();
	system("cls");
}