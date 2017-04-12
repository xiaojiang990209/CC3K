#include"Player.h"
#include"TextPanel.h"
#include<string>
#include<sstream>
#include<iostream>

Player::Player(int x, int y, std::string type, int hp, int atk, int def, bool isVisible) :Character(x, y, '@', type, hp, atk, def)
{
	this->isVisible = isVisible;
	this->gold = 0;
	this->stopwander = false;
	this->stopdeath = false;
	this->quit = false;
	this->restart = false;
}

bool Player::attackPlayer(int x, int y)
{
	Floor *f = Floor::getInstance();
	//Detect if there is enemy
	if (f->getMap()[this->getY() + y][this->getX() + x] == 'X' ||
		f->getMap()[this->getY() + y][this->getX() + x] == 'g' ||
		f->getMap()[this->getY() + y][this->getX() + x] == 'M' ||
		f->getMap()[this->getY() + y][this->getX() + x] == 'O' ||
		f->getMap()[this->getY() + y][this->getX() + x] == 'D'
		)
	{
		//If there is enemy, get it from floor
		Character *c = f->getEnemyFromCoordinate(this->getX() + x, this->getY() + y);
		//Attack that enemy
		this->combat(c);
		//If player belongs to Samurai class, change its visibility
		if (this->getType() == "Samurai")
		{
			this->setIsVisible(true);
		}
		return true;
	}
	return false;
}

bool Player::drinkPotion(int x, int y)
{
	Floor *f = Floor::getInstance();
	//Detect if there is potion
	if (f->getMap()[this->getY() + y][this->getX() + x] == '!')
	{
		//Acquire potion from floor.
		Potion *p = f->getPotionFromCoordinate(this->getX() + x, this->getY() + y);
		//Use potion
		this->usePotion(p);
		//Display the potion usage on the panel.
		TextPanel::appendMessage("You chug the " + p->getType() + "\n");
		return true;
	}
	return false;
}

bool Player::collectGold(int x, int y)
{
	Floor *f = Floor::getInstance();
	//Detect if there is gold
	if (f->getMap()[this->getY() + y][this->getX() + x] == '$')
	{
		//Acquire potion from floor
		Treasure *t = f->getTreasureFromCoordinate(this->getX() + x, this->getY() + y);
		//Collect gold
		this->gold += t->getNumGold();
		t->setIsUsed(true);
		return true;
	}
	return false;
}

bool Player::move(int x, int y)
{
	Floor *f = Floor::getInstance();
	//Detect if the chosen coordinate can be walked upon
	//Either floor tiles or passage ways.
	if (f->getMap()[this->getY() + y][this->getX() + x] == '.'||
		f->getMap()[this->getY() + y][this->getX() + x] == '#'||
		f->getMap()[this->getY() + y][this->getX() + x] == '+'||
		f->getMap()[this->getY() + y][this->getX() + x] == '>')
	{
		Floor::getInstance()->restoreMapFromCoordinate(this->getX(),this->getY());
		this->setX(this->getX() + x);
		this->setY(this->getY() + y);
		Floor::getInstance()->getMap()[this->getY()][this->getX()] = this->getDisplay();
		return true;
	}
	return false;
}

bool Player::getIsVisible()
{
	return this->isVisible;
}

void Player::setIsVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

int Player::getGold()
{
	return this->gold;
}

void Player::setGold(int gold)
{
	this->gold = gold;
}

void Player::directionIntepreter(std::string dir, int &x, int &y)
{
	if (dir == "ea")
	{
		x = 1; y = 0;
	}
	else if (dir == "we")
	{
		x = -1; y = 0;
	}
	else if (dir == "no")
	{
		x = 0; y = -1;
	}
	else if (dir == "so")
	{
		x = 0; y = 1;
	}
	else if (dir == "ne")
	{
		x = 1; y = -1;
	}
	else if (dir == "nw")
	{
		x = -1; y = -1;
	}
	else if (dir == "se")
	{
		x = 1; y = 1;
	}
	else if (dir == "sw")
	{
		x = -1; y = 1;
	}
}


bool Player::getStopWander()
{
	return this->stopwander;
}

bool Player::getStopDeath()
{
	return this->stopdeath;
}

bool Player::getRestart()
{
	return this->restart;
}

bool Player::getQuit()
{
	return this->quit;
}

void Player::update()
{
	std::string dir, line;
	int x=0, y=0;
	while (true)
	{
		std::cout << "What will you do ?" << std::endl;
		getline(std::cin, line);
		if (line[0] == 'r')
		{
			this->restart = true;
			return;
		}
		else if (line[0] == 'q')
		{
			this->quit = true;
			return;
		}
		else if (line == "stopwander")
		{
			this->stopwander = true;
			return;
		}
		else if (line == "stopdeath")
		{
			this->stopdeath = true;
			return;
		}
		else if (line[0] == 'a')
		{
			//Known command, now get direction
			std::stringstream ss(line);
			ss >> dir >> dir;
			this->directionIntepreter(dir, x, y);
			if (this->attackPlayer(x, y))
			{
				break;
			}
			else
			{
				std::cout << "There is no one to attack!" << std::endl;
				continue;
			}

		}
		else if (line[0] == 'u')
		{
			//Known command, now get direction
			std::stringstream ss(line);
			ss >> dir >> dir;
			this->directionIntepreter(dir, x, y);
			if (this->drinkPotion(x, y))
			{
				break;
			}
			else if (this->collectGold(x, y))
			{
				break;
			}
			else
			{
				std::cout << "There is nothing to use!" << std::endl;
				continue;
			}
		}
		else
		{
			dir = line;
			this->directionIntepreter(dir, x, y);
			if (this->move(x, y))
			{
				break;
			}
			else if (this->collectGold(x, y))
			{
				break;
			}
			else
			{
				std::cout << "You cannot move there!" << std::endl;
				continue;
			}
		}
	}
}


//----------------------------------------------------------------------------------------------
//Knight¿‡
Knight::Knight(int x, int y) :Player(x, y, "Knight", 100, 50, 50, true)
{

}




//----------------------------------------------------------------------------------------------
//Wizard¿‡
Wizard::Wizard(int x, int y) :Player(x, y, "Wizard", 60, 25, 0, true)
{

}

bool Wizard::attackPlayer(int x, int y)
{
	int curX = this->getX() + x;
	int curY = this->getY() + y;
	std::vector<std::string> map = Floor::getInstance()->getMap();
	//Wizard has a powerful long range attack and he can attack anything in a straight line in front of him
	//Continue forever until an enemy is found. If cannot be found, break;
	while (true)
	{
		//Temp variable to store currently probing position
		char c = map[curY][curX];
		if (c == 'X' || c == 'g' || c == 'M' ||
			c == 'O' || c == 'D')
		{
			//An enemy is found
			this->combat(Floor::getInstance()->getEnemyFromCoordinate(curX, curY));
			return true;
		}
		if (c == '-' || c == '|' || c == '+')
		{
			//The route hits the wall.
			return false;
		}
		curX += x;
		curY += y;
	}
}

//----------------------------------------------------------------------------------------------
//Samurai¿‡
Samurai::Samurai(int x, int y) :Player(x, y, "Samurai", 80, 50, 15, false)
{

}
