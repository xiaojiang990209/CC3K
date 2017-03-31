#include "Enemy.h"
#include<vector>
#include<utility>
#include<cstdlib>


//--------------------------------------------------------------------------------------------------------------------------------------------------
//Enemy��
Enemy::Enemy(int x, int y, char display, std::string type, int hp, int atk, int def, bool isHostile):Character(x,y,display,type, hp, atk, def)
{
	this->isHostile = isHostile;
}

bool Enemy::findEnemy(int x, int y)
{
	char c = this->getFloor()->getMap()[y][x];
	return c == '@';
}

bool Enemy::findPotion(int x, int y)
{
	char c =this->getFloor()->getMap()[y][x];
	return c == '!';
}

bool Enemy::attackPlayer()
{
	Player *p = this->getFloor()->getPlayer();
	//ѭ���Լ���Χ��8��λ��
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//������Լ���������
			if ((x == 0 && y == 0)) continue;
			if ((this->getX() + x) == p->getX() && (this->getY() + y) == p->getY())
			{
				this->combat(p);
				return true;
			}
		}
	}
	return false;
}

bool Enemy::getIsHostile()
{
	return this->isHostile;
}

void Enemy::setIsHostile(bool isHostile)
{
	this->isHostile = isHostile;
}

/***********************************************************************************************************

	drinkPotion() δ���ʵ��

*/
bool Enemy::drinkPotion()
{
	std::vector<std::string> map = this->getFloor()->getMap();
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if ((x == 0 && y == 0))continue;
			if (map[this->getY() + y][this->getX() + x] == '!')
			{
				/*
					1. ��Floor��Chamber���ҵ�����(this->getX()+x,this->getY()+y)��Potion
					2. ʹ�����Potion
						a. ��floor��ʹ��getChamberFromCoordinate(int x, int y)�ҵ�potion�����ĸ�Chamber
						b. ��Chamber�л�ȡpotionList����potionList���ҵ�Ҫʹ�õ�potion
						c. ��potion����ֵ�ӵ�character�ϣ�curFloor{HP|ATK|DEF}Boost()
						d. ��potion��isUsed���ó�true������chamber��update()���԰����potion��potionList��ɾȥ

				*/
				Potion *p = this->getFloor()->getPotionFromCoordinate(this->getX() + x, this->getY() + y);
				this->usePotion(p);
			}
		}
	}
}

void Enemy::moveRandomly()
{
	std::vector<std::string> map = this->getFloor()->getMap();
	std::vector<std::pair<int, int> > possibleNextSteps;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//������Լ���������
			if ((x == 0 && y == 0)) continue;
			if (map[this->getY() + y][this->getX() + x] == '.')
			{
				//��ӿ��ܵ���һ��
				possibleNextSteps.push_back(std::make_pair(x, y));
			}
		}
	}
	//�����һ����λ�ÿ����ߵĻ�
	if (possibleNextSteps.size() != 0)
	{
		//�����ȡһ��pair<int, int> ��Ϊ��һ����λ��
		std::pair<int, int> nextStep = possibleNextSteps[rand() % possibleNextSteps.size()];
		//��map֮ǰ��x,yλ�øĳ� '.'
		map[this->getY()][this->getX()] = '.';
		//����x,yֵ
		this->setX(this->getX() + nextStep.first);
		this->setY(this->getY() + nextStep.second);
		//����map�ϵ���x,yλ��ΪGridbug��ͼ��
		map[this->getY()][this->getX()] = this->getDisplay();

	}
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
//GridBug��
GridBug::GridBug(int x, int y) :Enemy(x, y, 'X', "GridBug", 50, 20, 10, true)
{

}


/*
	��ΪGridBug�趨������б���ƶ��͹�������������attackPlayer()��moveRandomly()����д
	Ϊ��ȥ��ֹ����б���˶��͹���
*/
bool GridBug::attackPlayer()
{
	Player *p = this->getFloor()->getPlayer();
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//��Ϊcannot attack or move diagonally.
			if ((x == 0 && y == 0) || (x == 1 && y == 1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == -1 && y == -1)) continue;
			/*if (this->findEnemy(this->getX()+x, this->getY()+y))
			{

			}*/
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
	std::vector<std::string> map = this->getFloor()->getMap();
	std::vector<std::pair<int, int> > possibleNextSteps;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			//��Ϊcannot attack or move diagonally.
			if ((x == 0 && y == 0) || (x == 1 && y == 1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == -1 && y == -1)) continue;
			if (map[this->getY() + y][this->getX() + x] == '.')
			{
				possibleNextSteps.push_back(std::make_pair(x, y));
			}
		}
	}
	//�����һ����λ�ÿ����ߵĻ�
	if (possibleNextSteps.size() != 0)
	{
		//�����ȡһ��pair<int, int> ��Ϊ��һ����λ��
		std::pair<int, int> nextStep = possibleNextSteps[rand() % possibleNextSteps.size()];
		//��map֮ǰ��x,yλ�øĳ� '.'
		map[this->getY()][this->getX()] = '.';
		//����x,yֵ
		this->setX(this->getX() + nextStep.first);
		this->setY(this->getY() + nextStep.second);
		//����map�ϵ���x,yλ��ΪGridbug��ͼ��
		map[this->getY()][this->getX()] = this->getDisplay();

	}
}

/*

	���ԸĽ��ĵط���
		1. ��update()�ֳɼ����������õĲ��֣�attackPlayer()��moveRandomly()��drinkPotion()���������Ƿ���baseClass���Ϊvirtual function()
		2. �����Ļ�����ʵ�ֲ�ͬ���˵�update()��ʱ�򣬿��Ը������ǲ�ͬ�Ĺ��ܣ���ʹ��������������������γ�update()
		3. ����һ���ô��������������subFunction���������в�һ����ʵ�ֵĻ���ֻ��Ҫ����������дĳһ��function�Ϳ�����


*/
void GridBug::update()
{
	//����Ҳ������˹�����������ƶ�
	if (!this->attackPlayer())
	{
		this->moveRandomly();
	}
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
//Goblin��
Goblin::Goblin(int x, int y) :Enemy(x, y, 'g', "Goblin", 75, 30, 20, true)
{

}

/*
	ִ��˳��
		1. �����Player����������Player
		2. �����Potion�ȣ���Potion
		3. �����û��Player������Ҳû��Potion�ȣ�������ƶ�
*/
void Goblin::update()
{
	//���Թ���Player
	if (!Enemy::attackPlayer())
	{
		//���Ժ�Potion
		if (!Enemy::drinkPotion())
		{
			//�����û��������û��ҩˮ��������ƶ�
			Enemy::moveRandomly();
		}
	}
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
//Merchant��
Merchant::Merchant(int x, int y) : Enemy(x, y, 'M', "Merchant", 100, 75, 5, false)
{

}

/*
	ִ��˳��
		1. �����Player�е��⣬����Player����������Player
		2. �����Playerû�е��⣬����û���ҵ�Player������������ƶ�
*/
void Merchant::update()
{
	bool skipMove = false;
	//�����Player�е��⣬���Թ���Player
	if (this->getIsHostile())
	{
		skipMove = Enemy::attackPlayer();
	}
	//����Ѿ������ɹ����������ƶ�
	if (!skipMove)
	{
		Enemy::moveRandomly();
	}
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
//Orc��
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
//Dragon��
Dragon::Dragon(int x, int y) :Enemy(x, y, 'D', "Dragon", 150, 50, 10, true)
{

}

/*
	��ΪDragonֻ����Dragon Hoard�����Ҳ����뿪��
	����Dragon��update()����ֻ�й���Player��û������ƶ�
*/
void Dragon::update()
{
	Enemy::attackPlayer();
}
