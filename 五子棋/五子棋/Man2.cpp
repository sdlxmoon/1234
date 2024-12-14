#include "Man2.h"


void Man2::init(Chess* chess)
{
	this->chess = chess;
}

void Man2::go()
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 50;
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(240, 620, _T("该白棋了"));
	MOUSEMSG msg;
	Chesspos pos;
	while (1) {
		msg = GetMouseMsg(); //获取鼠标信息
		if (msg.uMsg == WM_LBUTTONDOWN && chess->checkclick(msg.x, msg.y, &pos)) { //判断是否为有效点击
			break; //点击有效跳出循环
		}
	}
	chess->Chessdown(&pos, CHESS_White);
}
