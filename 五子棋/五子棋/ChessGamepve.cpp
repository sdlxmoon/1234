#include "chess.h"
#include "ChessGamepve.h"
ChessGamepve::ChessGamepve(Man1* man1, AI* ai, Chess* chess)
{
	this->man1 = man1;
	this->ai = ai;
	this->chess = chess;
	man1->init(chess);
	ai->init(chess);
}

void ChessGamepve::play()
{
	int g=fopen_s(&chess->fp, "C:\\Users\\李鑫\\source\\repos\\五子棋\\对局数据.txt", "w+");
	if (g != 0) {
		MessageBox(0, _T("存储文件打开失败"), _T("error"), 0);
		return;
	}
	int c = 0;
	chess->init();
	while (1) {
		man1->go();
		if (chess->gamecheck()) {
			fclose(chess->fp);
			chess->fp = NULL;
			LOGFONT f;
			gettextstyle(&f);
			f.lfHeight = 50;
			f.lfQuality = ANTIALIASED_QUALITY;
			settextstyle(&f);
			outtextxy(240, 620, _T("黑棋胜利"));
			MessageBox(0, _T("您胜利了，不要骄傲！！"), _T("漂亮"), 0);
			MOUSEMSG mag1;
			while (1) {
				mag1 = GetMouseMsg();
				if (mag1.uMsg == WM_LBUTTONDOWN && mag1.x > 20 && mag1.x < 159 && mag1.y>748 && mag1.y < 796) {
					chess->init();
					int g = fopen_s(&chess->fp, "C:\\Users\\李鑫\\source\\repos\\五子棋\\对局数据.txt", "w+");
					if (g != 0) {
						MessageBox(0, _T("存储文件打开失败"), _T("error"), 0);
						return;
					}
					c = 1;
					break;
				}
				else if (mag1.uMsg == WM_LBUTTONDOWN && mag1.x > 466 && mag1.x < 676 && mag1.y>748 && mag1.y < 796) {
					break;
				}
			}
			if (c == 1) continue;
			else if (c == 0) break;
		}
		ai->go();
		if (chess->gamecheck()) {
			fclose(chess->fp);
			chess->fp = NULL;
			LOGFONT f;
			gettextstyle(&f);
			f.lfHeight = 50;
			f.lfQuality = ANTIALIASED_QUALITY;
			settextstyle(&f);
			outtextxy(240, 620, _T("白棋胜利"));
			MessageBox(0, _T("你输了！！"), _T("别气馁"), 0);
			MOUSEMSG mag1;
			while (1) {
				mag1 = GetMouseMsg();
				if (mag1.uMsg == WM_LBUTTONDOWN && mag1.x > 20 && mag1.x < 159 && mag1.y>748 && mag1.y < 796) {
					chess->init();
					int g = fopen_s(&chess->fp, "C:\\Users\\李鑫\\source\\repos\\五子棋\\对局数据.txt", "w+");
					if (g != 0) {
						MessageBox(0, _T("存储文件打开失败"), _T("error"), 0);
						return;
					}
					c = 1;
					break;
				}
				else if (mag1.uMsg == WM_LBUTTONDOWN && mag1.x > 466 && mag1.x < 676 && mag1.y>748 && mag1.y < 796) {
					break;
				}
			}
			if (c == 1) continue;
			else if (c == 0) break;
		}
	}
}
