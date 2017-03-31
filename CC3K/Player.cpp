#include"Player.h"

Player::Player(int x, int y, std::string type, int hp, int atk, int def) :Character(x, y, '@', type, hp, atk, def)
{
	this->attackedMerchant = false;
	this->gold = 0;
	this->score = 0;
}

int Player::getGold()
{
	return this->gold;
}

int Player::getScore()
{
	return this->score;
}

void Player::setGold(int gold)
{
	this->gold = gold;
}

void Player::update()
{

}




//----------------------------------------------------------------------------------------------
//Knight¿‡
Knight::Knight(int x, int y) :Player(x, y, "Knight", 100, 50, 50)
{

}

void Knight::update()
{

}




//----------------------------------------------------------------------------------------------
//Wizard¿‡
Wizard::Wizard(int x, int y) :Player(x, y, "Wizard", 60, 25, 0)
{

}

void Wizard::update()
{

}





//----------------------------------------------------------------------------------------------
//Samurai¿‡
Samurai::Samurai(int x, int y) :Player(x, y, "Samurai", 80, 50, 15)
{

}

void Samurai::update()
{

}
