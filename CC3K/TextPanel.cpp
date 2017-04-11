#include"TextPanel.h"
#include<iostream>

std::string TextPanel::message = "";

TextPanel::TextPanel()
{

}

void TextPanel::appendMessage(std::string message)
{
	TextPanel::message += message;
}

void TextPanel::outputStates()
{
	Player *p = Floor::getInstance()->getPlayer();
	std::cout << "\tClass:" << p->getType();
	std::cout << "\tGP:" << p->getGold();
	std::cout << "\tFloor:" << Floor::getInstance()->getLevel();
	std::cout << std::endl;
	std::cout << "\tHP:" << p->getHP() << "/" << p->getInitHp();
	std::cout << "\tAtk:" << p->getATK();
	std::cout << "\tDef:" << p->getDEF() << "%";
	std::cout << std::endl;
}

void TextPanel::outputMessage()
{
	std::cout << message << std::endl;
	message = "";
}