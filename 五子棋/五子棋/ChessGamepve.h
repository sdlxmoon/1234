#pragma once
#include"AI.h"
#include"Man1.h"
class ChessGamepve
{
public:
	ChessGamepve(Man1* man1, AI* ai, Chess* chess);
	void play();
private:
	Man1* man1;
	AI* ai;
	Chess* chess;
};

