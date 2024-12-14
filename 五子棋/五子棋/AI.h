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
	// �洢������λ�������������ΪAI��������
	vector<vector<int>> scoreMap;
	Chesspos think();
};

