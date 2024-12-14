#include <stdio.h>
#include<easyx.h>
#include<mmsystem.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
#include "Chess.h"
#include "ChessGamepve.h"
#include "ChessGamepvp.h"
#include "Man1.h"
#include "AI.h"
#include "Man2.h"
#include "start.h"

int main() {
	Man1 man1;
	Man2 man2;
	AI ai;
	Chess chess(15, 76, 50, 40);
	ChessGamepve gamepve(&man1, &ai, &chess);
	ChessGamepvp gamepvp(&man1, &man2, &chess);
	start start;
	long long n = 1;
	while (n++) {
		int sel;
		if (n == 2) {
			start.loading();
		}
		sel = start.select();
		if (sel == 1) {
			gamepve.play();
			n = 1;
		}
		else if (sel  == 2) {
			gamepvp.play();
			n = 1;
		}
		else if (sel == 3) {
			chess.readfile();
			n = 1;
		}
		else if (sel == 0) {
			break;
		}
	}
	return 0;
}