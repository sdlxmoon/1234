#pragma once
#include"Chess.h"
#include"Man1.h"
#include"Man2.h"
class ChessGamepvp
{
public:
	ChessGamepvp(Man1* man1, Man2* man2, Chess* chess);
	void play();
private:
	Man1* man1;
	Man2* man2;
	Chess* chess;
};

