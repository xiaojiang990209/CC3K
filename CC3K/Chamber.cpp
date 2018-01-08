/**
 * Revised on Jan 7, 2018.
 * @author: Zijie Jiang
 * Changes: Added comments
 * 
 */

#include"Chamber.h"
#include"Floor.h"
#include<iostream>
Chamber::Chamber(int x, int y, int length, int width, int chamberIndex) :Entity(x, y, '.', "Chamber")
{
	this->length = length;
	this->width = width;
	this->hasPlayer = false;
	this->hasStairs = false;
	this->initXBoundaries(chamberIndex);
}

Chamber::~Chamber()
{
	characterList.clear();
	potionList.clear();
	treasureList.clear();
}

void Chamber::initXBoundaries(int chamberIndex)
{
	switch (chamberIndex)
	{
	case 0:
	case 2:
	case 3:
		for (int i = 0; i < this->getLength(); i++)
		{
			for (int j = 0; j < this->getWidth(); j++)
			{
				xBoundaries[this->getY() + i] = std::make_pair(this->getX(), this->getX() + this->getWidth());
			}
		}
		break;
	case 1:
		xBoundaries[3] = std::make_pair(39, 61);
		xBoundaries[4] = std::make_pair(39, 61);
		xBoundaries[5] = std::make_pair(39, 69);
		xBoundaries[6] = std::make_pair(39, 72);
		for (int i = 7; i <= 12; i++)
		{
			xBoundaries[i] = std::make_pair(61, 75);
		}
		break;
	case 4:
		for (int i = 16; i <= 18; i++)
		{
			xBoundaries[i] = std::make_pair(65, 75);
		}
		for (int i = 19; i <= 22; i++)
		{
			xBoundaries[i] = std::make_pair(37, 75);
		}
	}
}

void Chamber::initChamber()
{
	this->characterList.clear();
	this->potionList.clear();
	this->treasureList.clear();
	this->hasPlayer = false;
	this->hasStairs = false;
}

void Chamber::updateCharacterList()
{
	std::vector<Character*>::iterator it = this->characterList.begin();
	while (it != characterList.end())
	{
		//Update Character, only if the flag Floor::stopwander is false
		if (!Floor::getInstance()->getPlayer()->getStopWander())
		{
			(*it)->update();
		}
		//如果it指向的Character死了，则把Character从list中删去
		if ((*it)->getIsDead()) 
		{ 
			int lastX = (*it)->getX();
			int lastY = (*it)->getY();
			//Assign appropriate potions and treasures to the last coordinate of the dead enemy
			if ((*it)->getType() == "GridBug")
			{
				int num = rand() % 6;
				switch (num)
				{
				case 0:addPotion(new RestoreHealthPotion(lastX, lastY)); break;
				case 1:addPotion(new BoostAtkPotion(lastX, lastY)); break;
				case 2:addPotion(new BoostDefPotion(lastX, lastY)); break;
				case 3:addPotion(new PoisonHealthPotion(lastX, lastY)); break;
				case 4:addPotion(new WoundAtkPotion(lastX, lastY)); break;
				case 5:addPotion(new WoundDefPotion(lastX, lastY)); break;
				}
				//Update enemy display:char to potion display:char
				Floor::getInstance()->getMap()[lastY][lastX] = '!';
			}
			else if ((*it)->getType() == "Goblin" || (*it)->getType() == "Merchant" || (*it)->getType() == "Dragon")
			{
				//Update enemy display:char to treasure display:char
				Floor::getInstance()->getMap()[lastY][lastX] = '$';
				addTreasure(new GoldPile(lastX, lastY));
			}
			//If the enemy does not produce neither potion nor treasure, replace it with a '.' default board character
			else
			{
				Floor::getInstance()->getMap()[lastY][lastX] = '.';
			}
			delete *it;
			it = characterList.erase(it);
		}
		else 
		{
			++it; 
		}
	}
}

void Chamber::updatePotionList()
{
	//Same as updateCharacterList
	std::vector<Potion*>::iterator it = this->potionList.begin();
	while (it != potionList.end())
	{
		if ((*it)->getIsUsed())
		{
			//Restore map to '.' from '!' since potion is used.
			Floor::getInstance()->getMap()[(*it)->getY()][(*it)->getX()] = '.';
			it = potionList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Chamber::updateTreasureList()
{
	//Same as updateCharacterList
	std::vector<Treasure*>::iterator it = this->treasureList.begin();
	while (it != treasureList.end())
	{
		if ((*it)->getIsUsed())
		{
			//Restore map to '.' from '$' since treasure is used.
			Floor::getInstance()->getMap()[(*it)->getY()][(*it)->getX()] = '.';
			it = treasureList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Chamber::addCharacter(Character *c)
{
	this->characterList.push_back(c);
	Floor::getInstance()->getMap()[c->getY()][c->getX()] = c->getDisplay();
}

void Chamber::addPotion(Potion *p)
{
	this->potionList.push_back(p);
	Floor::getInstance()->getMap()[p->getY()][p->getX()] = p->getDisplay();
}

void Chamber::addTreasure(Treasure *t)
{
	this->treasureList.push_back(t);
	Floor::getInstance()->getMap()[t->getY()][t->getX()] = t->getDisplay();
}

bool Chamber::isInChamber(int x, int y)
{
	return this->xBoundaries[y].first < x&&x < this->xBoundaries.at(y).second;
}

int Chamber::getLength()
{
	return this->length;
}

int Chamber::getWidth()
{
	return this->width;
}

bool Chamber::getHasPlayer()
{
	return this->hasPlayer;
}

bool Chamber::getHasStairs()
{
	return this->hasStairs;
}

void Chamber::setHasPlayer(bool hasPlayer)
{
	this->hasPlayer = hasPlayer;
}

void Chamber::setHasStairs(bool hasStairs)
{
	this->hasStairs = hasStairs;
}

Character* Chamber::getCharacter(int x, int y)
{
	for (Character *c : this->characterList)
	{
		if (c->getY() == y&&c->getX() == x)
		{
			return c;
		}
	}
	return nullptr;
}

Potion* Chamber::getPotion(int x, int y)
{
	for (Potion *p : this->potionList)
	{
		if (p->getY() == y&&p->getX() == x)
		{
			return p;
		}
	}
	return nullptr;
}

Treasure* Chamber::getTreasure(int x, int y)
{
	for (Treasure *t : this->treasureList)
	{
		if (t->getY() == y&&t->getX() == x)
		{
			return t;
		}
	}
	return nullptr;
}

void Chamber::updateChamber()
{
	this->updateCharacterList();
	this->updatePotionList();
	this->updateTreasureList();
}