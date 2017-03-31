#include"TextPanel.h"

TextPanel::TextPanel(int level, Player *p)
{
	this->level = level;
	this->p = p;
}

int TextPanel::setLevel(int level)
{
	this->level = level;
}

void TextPanel::appendMessage(std::string message)
{
	this->message += message;
}

void TextPanel::update()
{
	std::cout << message << endl;
}