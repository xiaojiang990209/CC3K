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

Knight::Knight(int x, int y) :Player(x, y, "Knight", 100, 50, 50)
{

}