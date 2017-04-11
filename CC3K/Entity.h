#pragma once
#include<string>
class Entity {
private:
	int x;
	int y;
	char display;
	std::string type;
public:
	Entity(int x, int y, char display, std::string type);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	char getDisplay();
	std::string getType();
};