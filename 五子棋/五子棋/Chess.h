#pragma once
#include <math.h>
#include"graphics.h"
#include "vector"
using namespace std;
struct Chesspos
{
	int row;
	int col;
	Chesspos(int r = 0, int c = 0) :row(r), col(c) {}
};
typedef enum {
	CHESS_White = 1,
	CHESS_Black = -1
}chesskind;
class Chess
{
public:
	Chess(int size,int maginx, int maginy, float  chesssize);
	void init();
	bool checkclick(int x, int y,Chesspos*pos);
	void Chessdown(Chesspos* pos, chesskind kind);
	void Chessdownr(Chesspos* pos, chesskind kind);
	int getsize();
	bool gamecheck();
	int chessdata(Chesspos* pos);
	int Chessdata(int row, int col);
	FILE *fp;
	void readfile();
	Chesspos pos1;
private:
	Chesspos* pos;
	float chesssize;
	int maginx;
	int maginy;
	IMAGE chesswhite;
	IMAGE chessblack;
	int size;
	bool player;
	vector<vector<int>> chessmap;
	void updatachessmap(Chesspos* pos);
	bool checkwin();
	Chesspos lastPos;
	void filewrite(Chesspos pos,chesskind kind);
};

