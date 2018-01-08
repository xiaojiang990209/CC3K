/**
 * Revised on Jan 7, 2018.
 * @author: Zijie Jiang
 * Changes: Added comments
 * 
 */

#include<iostream>
#include<fstream>
#include<string>
#include"Floor.h"
#include<ctime>

using namespace std;


/**
 * Reads default map from file system
 * 
 * @param the url of the txt file storing the map
 * @return the map as a vector of string
 *
 */
vector<string> readFile(string url);

int main()
{
	srand(time(NULL));
	Floor *floor = nullptr;
	while (true)
	{
		floor = Floor::getInstance();
		floor->initMap(readFile("defaultLevel.txt"));
		char playerChoice;
		cout << "Welcome to CC3K. Choose your race:" << endl;
		cout << "k: Knight. w: Wizard. s: Samurai." << endl;
		cin >> playerChoice;
		cin.ignore();
		switch (playerChoice)
		{
		case 'k':
			floor->setPlayer(new Knight(0, 0)); break;
		case 'w':
			floor->setPlayer(new Wizard(0, 0)); break;
		case 's':
			floor->setPlayer(new Samurai(0, 0)); break;
		}
		system("clear");

		//Initialize floor in constructor
		floor->initFloor();

		while (true)
		{
			// Update Floor as well as maps within Floor
			// Updates of Floor contain the updates of each chamber
			floor->update();

			//If player successfully reaches the stair of the fifth floor
			if (floor->getLevel() == 6)
			{
				cout << "You win!!" << endl;
				cout << "Your score is " << floor->getPlayer()->getGold() << endl;
				break;
			}

			//Output player's death only if player dies and stopdeath is false
			if (floor->getPlayer()->getIsDead() && !floor->getPlayer()->getStopDeath())
			{
				cout << "You die!!" << endl;
				cout << "Your score is " << floor->getPlayer()->getGold() << "!" << endl;
				break;
			}

			//If player quits game
			if (floor->getPlayer()->getQuit() || floor->getPlayer()->getRestart())
			{
				cout << "Game ends!" << endl;
				break;
			}
		}

		// If player restarts game
		if (!floor->getPlayer()->getRestart())
		{
			break;
		}
		floor->resetInstance();
	}

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
