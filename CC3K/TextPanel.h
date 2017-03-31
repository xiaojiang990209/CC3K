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
	//�趨��ǰ���ڼ�¥
	int setLevel(int level);
	//���õ�ǰһ��Ҫ��ʾ����Ϣ
	void appendMessage(std::string message);
	//��ʾ��ǰһ����ʾ����Ϣ
	void update();
};