#include "start.h"
#include <stdio.h>
#include <cmath>
#include "conio.h"
#include "graphics.h"
void start::loading()
{
	IMAGE hui;
	IMAGE tui;
	IMAGE pvp;
	IMAGE pve;
	loadimage(&pvp, "res/双人对弈.png", 221, 51, true);
	loadimage(&pve, "res/人机模式.png", 221, 51, true);
	loadimage(&hui, "res/对局回放.png", 221, 51, true);
	loadimage(&tui, "res/退出游戏.png", 221, 51, true);
	loadimage(&kaishi, "res/开始界面.jpg", 490, 735, true);
	initgraph(490, 735);
	putimage(0, 0, &kaishi);
	putimage(138, 242, &pvp);
	putimage(138, 320, &pve);
	putimage(138, 398, &hui);
	putimage(138, 470, &tui);
}

int  start::select()
{
	MOUSEMSG msg1;
	while (1) {
		msg1 = GetMouseMsg();
		if (selectpvpcheck(msg1.x, msg1.y)&& msg1.uMsg == WM_LBUTTONDOWN) {
			return 2;
		}
		else if (selectpvecheck(msg1.x, msg1.y)&&msg1.uMsg == WM_LBUTTONDOWN ){
			return 1;
		}
		else if(msg1.uMsg == WM_LBUTTONDOWN&&(msg1.x > 138 && msg1.x < 359)&&(398<msg1.y&&msg1.y<449)){
			return 3;
		}
		else if (msg1.uMsg == WM_LBUTTONDOWN && (msg1.x > 138 && msg1.x < 359) && (470 < msg1.y && msg1.y < 521)) {
			return 0;
		}
	}
}


bool start::selectpvpcheck(int x, int y)
{
	int a = x;
	int b = y;
	if ((a>138&&a<359) && (b>242&&b<293)) {
		return true;
	}
	return false;
}

bool start::selectpvecheck(int x, int y) {
	int a = x;
	int b = y;
	if ((a>138&&a<359) && (b>320&&b<371)) {
		return true;
	}
	return false;
}

