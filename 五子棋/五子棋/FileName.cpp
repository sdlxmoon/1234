#include <stdio,h>
#include <easyx.h>

int main() {
	initgraph(500,600);
	IMAGE th;
	loadimage(&th,"res/th.jpg");
	putimage(0, 0, &th);
	return 0;

}

