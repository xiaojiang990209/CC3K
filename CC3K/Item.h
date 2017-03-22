#pragma once
#include"Entity.h"
class Item :public Entity
{
private:
	bool isUsed;
public:
	Item(int x, int y, char display, std::string type);
	bool getIsUsed();
	virtual void effect();
};