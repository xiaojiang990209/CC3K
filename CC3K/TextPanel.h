#pragma once
#include"Player.h"
#include<string>
class TextPanel
{
private:
	int level;
	Player *p;
	std::string message;
public:
	TextPanel(int level, Player *p);
	//设定当前处在几楼
	int setLevel(int level);
	//设置当前一轮要显示的信息
	void appendMessage(std::string message);
	//显示当前一轮显示的信息
	void update();
};