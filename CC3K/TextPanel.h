#pragma once
#include"Floor.h"
#include<string>
class TextPanel
{
private:
	static std::string message;
public:
	TextPanel();
	//���õ�ǰһ��Ҫ��ʾ����Ϣ
	static void appendMessage(std::string message);
	//��ʾPlayer�ĸ�����Ϣ
	static void outputStates();
	//��ʾ��ǰһ����ʾ����Ϣ
	static void outputMessage();
};