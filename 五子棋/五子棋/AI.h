#pragma once
#include "Chess.h"

class AI
{
public:
	void init(Chess*chess);
	void go();
private:
	void caculatesorce();
private:
	Chess* chess;
	// 存储各个点位的评分情况，作为AI下棋依据
	vector<vector<int>> scoreMap;
	Chesspos think();
};

