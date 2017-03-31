#include"Floor.h"
#include<iostream>
#include<cstdlib>

using namespace std;

Floor::Floor()
{
	
}

void Floor::spawnPlayer()
{
	//���ѡ��һ��chamber
	int indexChamber = rand() % this->chambers.size();
	Chamber *c = this->chambers[indexChamber];
	//��ѡ�е�Chamber����¥�ݣ�����ѡ��
	while (c->getHasStairs())
	{
		indexChamber = rand() % this->chambers.size();
		c = this->chambers[indexChamber];
	}
	c->setHasPlayer(true);
	//�������x,y����
	int x = c->getX() + rand() % c->getWidth();
	int y = c->getY() + rand() % c->getLength();
	//�����ɵ�(x,y)��chamber�����map��λ������ '.' -> δ��ռ�� 
	while (!c->isInChamber(x, y)||this->map[y][x]!='.')
	{
		x = c->getX() + rand() % c->getWidth();
		y = c->getY() + rand() % c->getLength();
	}

	
}

void Floor::spawnStairs()
{
	//���ѡ��һ��chamber
	int indexChamber = rand() % this->chambers.size();
	Chamber *c = this->chambers[indexChamber];
	//��ѡ�е�Chamber����¥�ݣ�����ѡ��
	while (c->getHasPlayer())
	{
		indexChamber = rand() % this->chambers.size();
		c = this->chambers[indexChamber];
	}
	c->setHasStairs(true);
	//�������x,y����
	int x = c->getX() + rand() % c->getWidth();
	int y = c->getY() + rand() % c->getLength();
	//�����ɵ�(x,y)��chamber�����map��λ������ '.' -> δ��ռ�� 
	while (!c->isInChamber(x, y) || this->map[y][x] != '.')
	{
		x = c->getX() + rand() % c->getWidth();
		y = c->getY() + rand() % c->getLength();
	}

	this->stair = new Entity(x, y, '>', "Stairs");
	this->map[y][x] = '>';
}

void Floor::generateFloor()
{

}

Floor* Floor::getInstance()
{

}

void Floor::outputFloor()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].length(); j++)
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

void Floor::initMap(std::vector<std::string> map)
{
	this->initMap = this->map = map;
}

std::vector<std::string>& Floor::getMap()
{
	return map;
}

Character* Floor::getEnemyFromCoordinate(int x, int y)
{
	Chamber *chamber = nullptr;
	for (Chamber *c: this->chambers)
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
	for (Chamber *c : this->chambers)
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
	for (Chamber *c : this->chambers)
	{
		if (c->isInChamber(x, y))
		{
			chamber = c;
			break;
		}
	}
	return chamber->getTreasure(x, y);
}