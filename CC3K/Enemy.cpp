#include "Enemy.h"
#include"Floor.h"
#include<vector>
#include<utility>
#include<cstdlib>
#include<iostream>


//--------------------------------------------------------------------------------------------------------------------------------------------------
//Enemy类
Enemy::Enemy(int x, int y, char display, std::string type, int hp, int atk, int def, bool isHostile):Character(x,y,display,type, hp, atk, def)
{
	this->isHostile = isHostile;
}

bool Enemy::findEnemy(int x, int y)
{
	char c = Floor::getInstance()->getMap()[y][x];
	return c == '@';
}

bool Enemy::getIsHostile()
{
	return this->isHostile;
}

void Enemy::setIsHostile(bool isHostile)
{
	this->isHostile = isHostile;
}

bool Enemy::findPotion(int x, int y)
{
	char c =Floor::getInstance()->getMap()[y][x];
	return c == '!';
}

bool Enemy::attackPlayer()
{
	//如果enemy对Player没有敌意，则不攻击，则返回false代表攻击不成功
	if (!this->getIsHostile()) return false;
	Player *p = Floor::getInstance()->getPlayer();
	if (!p->getIsVisible()) return false;
	//std::cout << "In attack Player!" << std::endl;

	//循环自己周围的8个位置
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//如果是自己本身，跳过
			if ((x == 0 && y == 0)) continue;
			//std::cout << this->getX() << ' ' << this->getY() << ' ' << x << ' ' << y << ' ' << p->getX() << ' ' << p->getY() << std::endl;

			if ((this->getX() + x) == p->getX() && (this->getY() + y) == p->getY())
			{
				this->combat(p);
				return true;
			}
		}
	}
	return false;
}

/***********************************************************************************************************

	drinkPotion() 未完成实现

*/
bool Enemy::drinkPotion()
{
	std::vector<std::string> map = Floor::getInstance()->getMap();
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if ((x == 0 && y == 0))continue;
			if (map[this->getY() + y][this->getX() + x] == '!')
			{
				/*
					1. 从Floor到Chamber，找到具有(this->getX()+x,this->getY()+y)的Potion
					2. 使用这个Potion
						a. 从floor中使用getChamberFromCoordinate(int x, int y)找到potion属于哪个Chamber
						b. 从Chamber中获取potionList，从potionList中找到要使用的potion
						c. 把potion的数值加到character上：curFloor{HP|ATK|DEF}Boost()
						d. 把potion的isUsed设置成true，这样chamber的update()可以把这个potion从potionList中删去

				*/
				Potion *p = Floor::getInstance()->getPotionFromCoordinate(this->getX() + x, this->getY() + y);
				this->usePotion(p);
				return true;
			}
		}
	}
	return false;
}

void Enemy::moveRandomly()
{
	std::vector<std::string> map = Floor::getInstance()->getMap();
	std::vector<std::pair<int, int> > possibleNextSteps;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//如果是自己本身，跳过
			if ((x == 0 && y == 0)) continue;
			if (map[this->getY() + y][this->getX() + x] == '.')
			{
				//添加可能的下一步
				possibleNextSteps.push_back(std::make_pair(x, y));
			}
		}
	}
	//如果下一步有位置可以走的话
	if (possibleNextSteps.size() != 0)
	{
		//随机获取一个pair<int, int> 作为下一步的位置
		std::pair<int, int> nextStep = possibleNextSteps[rand() % possibleNextSteps.size()];
		//将map之前的x,y位置改成 '.'
		Floor::getInstance()->getMap()[this->getY()][this->getX()] = '.';
		//更新x,y值
		this->setX(this->getX() + nextStep.first);
		this->setY(this->getY() + nextStep.second);
		//更新map上的新x,y位置为Gridbug的图标
		Floor::getInstance()->getMap()[this->getY()][this->getX()] = this->getDisplay();

	}
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
//GridBug类
GridBug::GridBug(int x, int y) :Enemy(x, y, 'X', "GridBug", 50, 20, 10, true)
{

}


/*
	因为GridBug设定，不能斜着移动和攻击，所以他的attackPlayer()和moveRandomly()得重写
	为了去禁止他的斜向运动和攻击
*/
bool GridBug::attackPlayer()
{
	//如果enemy对Player没有敌意，则不攻击，则返回false代表攻击不成功
	if (!this->getIsHostile()) return false;
	Player *p = Floor::getInstance()->getPlayer();
	if (!p->getIsVisible()) return false;
	//std::cout << "In gridbug attack Player!" << std::endl;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//因为cannot attack or move diagonally.
			if ((x == 0 && y == 0) || (x == 1 && y == 1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == -1 && y == -1)) continue;
			//std::cout << this->getX() << ' ' << this->getY() << ' ' << x << ' ' << y << ' ' << p->getX() << ' ' << p->getY() << std::endl;
			if ((this->getX() + x) == p->getX() && (this->getY() + y) == p->getY())
			{
				this->combat(p);
				return true;
			}
		}
	}
	return false;
}

void GridBug::moveRandomly()
{
	std::vector<std::string> map = Floor::getInstance()->getMap();
	std::vector<std::pair<int, int> > possibleNextSteps;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//因为cannot attack or move diagonally.
			if ((x == 0 && y == 0) || (x == 1 && y == 1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == -1 && y == -1)) continue;
			if (map[this->getY() + y][this->getX() + x] == '.')
			{
				possibleNextSteps.push_back(std::make_pair(x, y));
			}
		}
	}
	//如果下一步有位置可以走的话
	if (possibleNextSteps.size() != 0)
	{
		//随机获取一个pair<int, int> 作为下一步的位置
		std::pair<int, int> nextStep = possibleNextSteps[rand() % possibleNextSteps.size()];
		//将map之前的x,y位置改成 '.'
		Floor::getInstance()->getMap()[this->getY()][this->getX()] = '.';
		//更新x,y值
		this->setX(this->getX() + nextStep.first);
		this->setY(this->getY() + nextStep.second);
		//更新map上的新x,y位置为Gridbug的图标
		Floor::getInstance()->getMap()[this->getY()][this->getX()] = this->getDisplay();

	}
}

/*

	可以改进的地方：
		1. 把update()分成几个可以重用的部分：attackPlayer()，moveRandomly()，drinkPotion()，并把他们放在baseClass里，作为virtual function()
		2. 这样的话，在实现不同敌人的update()的时候，可以根据他们不同的功能，来使用以上三个函数来组合形成update()
		3. 还有一个好处：如果以上三个subFunction在子类中有不一样的实现的话，只需要在子类中重写某一个function就可以了


*/
void GridBug::update()
{
	//如果找不到敌人攻击，则随机移动
	if (!this->attackPlayer())
	{
		this->moveRandomly();
	}
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
//Goblin类
Goblin::Goblin(int x, int y) :Enemy(x, y, 'g', "Goblin", 75, 30, 20, true)
{

}

/*
	执行顺序：
		1. 如果有Player攻击，攻击Player
		2. 如果有Potion喝，喝Potion
		3. 如果又没有Player攻击，也没有Potion喝，则随机移动
*/
void Goblin::update()
{
	//尝试攻击Player
	if (!Enemy::attackPlayer())
	{
		//尝试喝Potion
		if (!Enemy::drinkPotion())
		{
			//如果又没攻击，又没喝药水，则随机移动
			Enemy::moveRandomly();
		}
	}
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
//Merchant类
Merchant::Merchant(int x, int y) : Enemy(x, y, 'M', "Merchant", 100, 75, 5, false)
{

}

/*
	执行顺序：
		1. 如果对Player有敌意，且有Player攻击，攻击Player
		2. 如果对Player没有敌意，或者没有找到Player攻击，则随机移动
*/
void Merchant::update()
{
	//如果Enemy::attackPlayer执行返回false，则代表：
	//		1. Merchant对Player没有敌意
	//		2. Merchant找不到Player攻击
	if (!Enemy::attackPlayer())
	{
		//如果已经攻击成功，则跳过移动
		Enemy::moveRandomly();
	}
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
//Orc类
Orc::Orc(int x, int y) :Enemy(x, y, 'O', "Orc", 120, 30, 30, true)
{

}

void Orc::update()
{
	if (!Enemy::attackPlayer())
	{
		Enemy::moveRandomly();
	}
}




//--------------------------------------------------------------------------------------------------------------------------------------------------
//Dragon类
Dragon::Dragon(int x, int y) :Enemy(x, y, 'D', "Dragon", 150, 50, 10, true)
{

}

/*
	因为Dragon只守卫Dragon Hoard，并且不会离开它
	所以Dragon的update()里面只有攻击Player，没有随机移动
*/
void Dragon::update()
{
	Enemy::attackPlayer();
}
