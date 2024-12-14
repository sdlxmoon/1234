#pragma once
#include"Chess.h"
class Man2
{
public:
	void init(Chess*chess);
	void go();
	int a = 0;
private:
	Chess* chess;
};

