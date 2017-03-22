#include"Item.h"

Item::Item(int x, int y, char display, std::string type) :Entity(x, y, display,type)
{
	this->isUsed = false;
}



bool Item::getIsUsed()
{
	return this->isUsed;
}

void Item::effect()
{

}

