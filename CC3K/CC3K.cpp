// CC3K.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Floor.h"

using namespace std;

vector<string> readFile(string url);
void movePlayer(int iniX, int iniY, int x, int y, vector<string> &floor, vector<string> &defaultFloor);

int main()
{
	Floor *floor = Floor::getInstance();
	floor->initMap(readFile("defaultLevel.txt"));
	int playerChoice;
	/*vector<string> defaultFloor = readFile("defaultLevel.txt");
	vector<string> floor(defaultFloor);

	int x = 9;
	int y = 5;
	floor[y][x] = '@';

	string command;
	while (true)
	{
		drawFloor(floor);
		int addX;
		int addY;
		cout << "What will you do:";
		cin >> command;
		if (!command.compare("no"))
		{
			addX = 0;
			addY = -1;
		}
		else if (!command.compare("so"))
		{
			addX = 0;
			addY = 1;
		}
		else if (!command.compare("ea"))
		{
			addX = 1;
			addY = 0;
		}
		else if (!command.compare("we"))
		{
			addX = -1;
			addY = 0;
		}
		else if (!command.compare("ne"))
		{
			addX = 1;
			addY = -1;
		}
		else if (!command.compare("nw"))
		{
			addX = -1;
			addY = -1;
		}
		else if (!command.compare("se"))
		{
			addX = 1;
			addY = 1;
		}
		else if (!command.compare("sw"))
		{
			addX = -1;
			addY = 1;
		}
		movePlayer(x, y, addX, addY, floor,defaultFloor);
		x += addX;
		y += addY;
		system("cls");
	}*/
	cout << "Welcome to CC3K. Choose your race:" << endl;
	cout << "1: Knight. 2: Wizard. 3: Samurai." << endl;
	cin >> playerChoice;
	cin.ignore();
	switch (playerChoice)
	{
	case 0:
		floor->setPlayer(new Knight(0, 0)); break;
	case 1:
		floor->setPlayer(new Wizard(0, 0)); break;
	case 2:
		floor->setPlayer(new Samurai(0, 0)); break;
	}
	
	floor->initFloor();
	


	//Initialize floor in constructor
	
	
	while (true)
	{
		//更新Floor以及Floor里的map
		//Floor更新里有每个Chamber的更新
		floor->update();
		////打印出当前Floor的map
		//floor->outputFloor();
		////打印出TextPanel
		//floor->outputTextPanel();
		////调用Player的update()， 询问Player的下一步
		//floor->getPlayer()->update();

	}


	system("pause");

    return 0;
}

vector<string> readFile(string url)
{
	vector<string> board;
	string line;
	ifstream in;
	in.open(url);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			board.push_back(line);
		}
	}
	else
	{
		cout << "Unable to open file." << endl;
	}
	return board;
}

void movePlayer(int iniX, int iniY, int x, int y, vector<string> &floor,vector<string> &defaultFloor)
{
	floor[iniY][iniX] = defaultFloor[iniY][iniX];
	floor[iniY+y][iniX+x] = '@';
}