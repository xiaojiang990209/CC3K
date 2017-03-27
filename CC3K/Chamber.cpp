#include"Chamber.h"
Chamber::Chamber(int x, int y, int length, int width) :Entity(x, y, '.', "Chamber")
{
	this->length = length;
	this->width = width;
	this->hasPlayer = false;
	this->hasStairs = false;
}

void Chamber::updateCharacterList()
{
	std::vector<Character*>::iterator it = characterList.begin();
	while (it != characterList.end())
	{
		// (*it)->update();     ¸üÐÂCharacter.
		// if(!(*it)->udpate()) { it=characterList.erase(it)} else{++it;}
	}
}

void Chamber::updatePotionList()
{
	//Same as updateCharacterList
}

void Chamber::updateTreasureList()
{
	//Same as updateCharacterList
}

void Chamber::addCharacter(Character *c)
{
	this->characterList.push_back(c);
}

void Chamber::addPotion(Potion *p)
{
	this->potionList.push_back(p);
}

void Chamber::addTreasure(Treasure *t)
{
	this->treasureList.push_back(t);
}

void Chamber::updateChamber()
{
	this->updateCharacterList();
	this->updatePotionList();
	this->updateTreasureList();
}

bool Chamber::isInChamber(int x, int y)
{
	return this->xBoundaries[y].first < x&&x < this->xBoundaries.at(y).second;
}

bool Chamber::hasPlayer()
{
	return this->hasPlayer;
}

bool Chamber::hasStairs()
{
	return this->hasStairs;
}