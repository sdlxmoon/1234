#include "Chess.h"
#include"easyx.h"
#include "WinUser.h"





void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}



Chess::Chess(int size, int maginx, int maginy, float chesssize)
{
	this->size = size;
	this->maginx = maginx;
	this->maginy = maginy;
	this->chesssize = chesssize;
	player = true;
	for (int i = 0; i < size; i++) {
		vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		chessmap.push_back(row);
	}
}

void Chess::init()
{
	IMAGE qp;
	IMAGE dt;
	loadimage(&dt, "res/��ͼ.png", 692, 187, true);
	loadimage(&qp, "res/����15.jpg",692,682,true);
	initgraph(692,869);
	putimage(0, 0, &qp);
	putimage(0, 682, &dt);
	loadimage(&chessblack, ("res/black.png"), chesssize, chesssize, true);
	loadimage(&chesswhite, ("res/white.png"), chesssize, chesssize, true);
	for (int i = 0; i < chessmap.size(); i++) {
		for (int j = 0; j < chessmap[i].size(); j++) {
			chessmap[i][j] = 0;
		}
	}
}

bool Chess::checkclick(int x, int y, Chesspos* pos) //�ж��Ƿ���Ч���
{
	int col = (x - maginx)/ chesssize;
	int row = (y - maginy)/ chesssize;
	if (col > 13 || row > 13||col<0||row<0) {
		return false;
	}
	int leftTopPosx = maginx+ chesssize*col;
	int leftTopPosy = maginy+chesssize*row;
	float offset =chesssize * 0.5;
	float len;
	bool ans = false;
	len = sqrt((x - leftTopPosx) * (x - leftTopPosx) + (y - leftTopPosy) * (y - leftTopPosy));
	do {
		if (len < offset) {
			pos->col = col;
			pos->row = row;
			if (chessmap[row][col] == 0) {
				ans = true;
				break;
			}
		}
		int rightTopPosx = leftTopPosx+chesssize; //���Ͻ�
		int rightTopPosy = leftTopPosy;
		len = sqrt((x - rightTopPosx) * (x - rightTopPosx) + (y - rightTopPosy) * (y - rightTopPosy));
		if (len < offset) {
			pos->col = col+1;
			pos->row = row;
			if (chessmap[row+1][col] == 0) {
				ans = true;
				break;
			}
		}
		int leftDownPosx = leftTopPosx;  //���½�
		int leftDownPosy = leftTopPosy + chesssize;
		len = sqrt((x - leftDownPosx) * (x - leftDownPosx) + (y - leftDownPosy) * (y - leftDownPosy));
		if (len < offset) {
			pos->col = col;
			pos->row = row+1;
			if (chessmap[row ][col+1] == 0) {
				ans = true;
				break;
			}
		}
		int rightDownPosx = leftTopPosx+chesssize; //���½�
		int rightDownPosy = leftTopPosy + chesssize;
		len = sqrt((x - rightDownPosx) * (x - rightDownPosx) + (y - rightDownPosy) * (y - rightDownPosy));
		if (len < offset) {
			pos->col = col + 1;
			pos->row = row + 1;
			if (chessmap[row+1][col + 1] == 0) {
				ans = true;
				break;
			}
		}
	} while (0);
	return ans;
}

void Chess::Chessdown(Chesspos* pos, chesskind kind) //����
{
	int x = maginx + chesssize * pos->col - 0.5 * chesssize;
	int y = maginy + chesssize * pos->row - 0.5 * chesssize;
	if (kind == CHESS_Black) {
		mciSendString("play res/down7.wav", 0, 0, 0);
		putimagePNG(x, y, &chessblack);
	}
	else if(kind==CHESS_White){
		mciSendString("play res/down7.wav", 0, 0, 0);
		putimagePNG(x, y, &chesswhite);
	}
	updatachessmap(pos);
}

void Chess::Chessdownr(Chesspos* pos, chesskind kind)
{
	int x = maginx + chesssize * pos->col - 0.5 * chesssize;
	int y = maginy + chesssize * pos->row - 0.5 * chesssize;
	if (kind == CHESS_Black) {
		mciSendString("play res/down7.wav", 0, 0, 0);
		putimagePNG(x, y, &chessblack);
	}
	else if (kind == CHESS_White) {
		mciSendString("play res/down7.wav", 0, 0, 0);
		putimagePNG(x, y, &chesswhite);
	}
}

int Chess::getsize()
{
	return size;
}

bool Chess::gamecheck()  //�ж���Ϸ�Ƿ����
{
	if (checkwin()) {
		return true;
	}
	return false;
}

int Chess::chessdata(Chesspos* pos)
{
	return chessmap[pos->row][pos->col];
}

int Chess::Chessdata(int row, int col)
{
	return chessmap[row][col];
}

void Chess::updatachessmap(Chesspos* pos)
{
	lastPos = *pos;
	chessmap[pos->row][pos->col] = player ? CHESS_Black : CHESS_White;
	filewrite(*pos, CHESS_Black);
	player = !player;
}

bool Chess::checkwin()
{
	// ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
	// ˮƽ����
	int row = lastPos.row;
	int col = lastPos.col;

	for (int i = 0; i < 5; i++)
	{
		// ����5��������ƥ��4���ӣ�20�����
		if (col - i >= 0 &&
			col - i + 4 < size &&
			chessmap[row][col - i] == chessmap[row][col - i + 1] &&
			chessmap[row][col - i] == chessmap[row][col - i + 2] &&
			chessmap[row][col - i] == chessmap[row][col - i + 3] &&
			chessmap[row][col - i] == chessmap[row][col - i + 4])
			return true;
	}

	// ��ֱ����(��������4��)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < size &&
			chessmap[row - i][col] == chessmap[row - i + 1][col] &&
			chessmap[row - i][col] == chessmap[row - i + 2][col] &&
			chessmap[row - i][col] == chessmap[row - i + 3][col] &&
			chessmap[row - i][col] == chessmap[row - i + 4][col])
			return true;
	}

	// ��/"����
	for (int i = 0; i < 5; i++)
	{
		if (row + i < size &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < size &&
			// ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
			chessmap[row + i][col - i] == chessmap[row + i - 1][col - i + 1] &&
			chessmap[row + i][col - i] == chessmap[row + i - 2][col - i + 2] &&
			chessmap[row + i][col - i] == chessmap[row + i - 3][col - i + 3] &&
			chessmap[row + i][col - i] == chessmap[row + i - 4][col - i + 4])
			return true;
	}

	// ��\�� ����
	for (int i = 0; i < 5; i++)
	{
		// ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
		if (row - i >= 0 &&
			row - i + 4 < size &&
			col - i >= 0 &&
			col - i + 4 < size &&
			chessmap[row - i][col - i] == chessmap[row - i + 1][col - i + 1] &&
			chessmap[row - i][col - i] == chessmap[row - i + 2][col - i + 2] &&
			chessmap[row - i][col - i] == chessmap[row - i + 3][col - i + 3] &&
			chessmap[row - i][col - i] == chessmap[row - i + 4][col - i + 4])
			return true;
	}

	return false;
}

void Chess::filewrite(Chesspos pos, chesskind kind)
{
	int a = pos.row;
	int b = pos.col;
	int c = player ? -1 : 1;
	fprintf(fp, "%d\t%d\t%d\t\n", a, b, c);
	return;
}

void Chess::readfile()
{
done:
	FILE* fp1=NULL;
	int error=fopen_s(&fp1, "C:\\Users\\����\\source\\repos\\������\\�Ծ�����.txt", "r+");
	if (error != 0) {
		MessageBox(0, _T("��ʧ��"), _T("error"), 0);
		perror("fopen_s");
		return;
	}
	init();
	while (1) {
		Chesspos* pos1=(Chesspos*)malloc(sizeof(Chesspos));
		int a, b, c;
		fscanf_s(fp1, "%d\t%d\t%d\t\n", &a, &b, &c);
		pos1->row = a;
		pos1->col = b;
		if (c == -1) {
			Chessdownr(pos1, CHESS_Black);
			Sleep(1500);
		}
		else if (c == 1) {
			Chessdownr(pos1, CHESS_White);
			Sleep(1500);
		}
		if (feof(fp1)) {
			break;
		}
	}
	while (1) {
		MOUSEMSG mag1;
		mag1 = GetMouseMsg();
		if (mag1.uMsg == WM_LBUTTONDOWN && mag1.x > 20 && mag1.x < 159 && mag1.y>748 && mag1.y < 796) {
			fclose(fp1);
			goto done;
			break;
		}
		else if (mag1.uMsg == WM_LBUTTONDOWN && mag1.x > 466 && mag1.x < 676 && mag1.y>748 && mag1.y < 796) {
			break;
		}
	}
	fclose(fp1);
	return;
}
