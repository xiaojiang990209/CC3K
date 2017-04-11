#include "Entity.h"

Entity::Entity(int x, int y, char display, std::string type)
{
	this->x = x;
	this->y = y;
	this->display = display;
	this->type = type;
}

void Entity::setX(int x)
{
	this->x = x;
}

void Entity::setY(int y)
{
	this->y = y;
}

int Entity::getX()
{
	return this->x;
}

int Entity::getY()
{
	return this->y;
}

char Entity::getDisplay()
{
	return this->display;
}

std::string Entity::getType()
{
	return this->type;
}
