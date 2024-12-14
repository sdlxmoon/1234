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
	outtextxy(240, 620, _T("�ð�����"));
	MOUSEMSG msg;
	Chesspos pos;
	while (1) {
		msg = GetMouseMsg(); //��ȡ�����Ϣ
		if (msg.uMsg == WM_LBUTTONDOWN && chess->checkclick(msg.x, msg.y, &pos)) { //�ж��Ƿ�Ϊ��Ч���
			break; //�����Ч����ѭ��
		}
	}
	chess->Chessdown(&pos, CHESS_White);
}
