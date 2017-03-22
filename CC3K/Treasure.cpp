#include"Treasure.h"
Treasure::Treasure(int x, int y, char display, std::string type, int numGold) : Item(x, y, display, type)
{
	this->numGold = numGold;
}

int Treasure::getNumGold()
{
	return this->numGold;
}

GoldPile::GoldPile(int x, int y) : Treasure(x, y, '$', "GoldPile", 10)
{

}

DragonHoard::DragonHoard(int x, int y) : Treasure(x, y, '$', "DragonHoard", 50)
{
	this->canBePickedUp = false;
}

bool DragonHoard::getCanBePickedUp()
{
	return this->canBePickedUp;
}

void DragonHoard::setCanBePickedUp(bool canBePickedUp)
{
	this->canBePickedUp = canBePickedUp;
}