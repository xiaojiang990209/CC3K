#pragma once
#include"Floor.h"
#include<string>
class TextPanel
{
private:
	static std::string message;
public:
	TextPanel();
	//设置当前一轮要显示的信息
	static void appendMessage(std::string message);
	//显示Player的各种信息
	static void outputStates();
	//显示当前一轮显示的信息
	static void outputMessage();
};