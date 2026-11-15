#define _CRT_SECURE_NO_WARNINGS
#define WIDTH 655
#define LENGTH 810
#define ROW 8
#define COL 8
#define XS 76
#define GAP 5
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")//引用winmm.lab库 对windows录音设备采集录音数据 
int arr[ROW][COL];
int x = GAP, y = 70, i, j;

MOUSEMSG userClick() {
	MOUSEMSG msg;
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && msg.y > y&&msg.x%(GAP+XS)>GAP&&(msg.y-y)%(GAP + XS)>GAP) {
			return msg;
		}
	}
}

bool Erase_xy(int x1,int x2,int y1,int y2) {
	if (x1 == x2) {
		for (i = (y1 < y2 ? y1 : y2) + 1;i < (y1 > y2 ? y1 : y2);i++) {
			if (arr[x1][i] != -1) {
				return false;
			}
		}
	}
	else if (y1 == y2) {
		for (i = (x1 < x2 ? x1 : x2) + 1;i < (x1 > x2 ? x1 : x2);i++) {
			if (arr[i][y1] != -1) {
				return false;
			}
		}
	}
	else if (arr[x1][y2] != -1 && arr[x2][y1] != -1) {
		return false;
	}
	else if (arr[x1][y2] == -1) {
		if (!(Erase_xy(x1, x1, y1, y2) && Erase_xy(x1, x2, y2, y2)))
			return false;
	}
	else if (arr[x2][y1] == -1) {
		if (!(Erase_xy(x1, x2, y1, y1) && Erase_xy(x2, x2, y1, y2)))
			return false;
	}
	else return true;
}


bool Erase_else(int x1, int x2, int y1, int y2) {
	int ci = 0, cj = 0;
	for (int i = 0;i < ROW;i++) {
		for (int j = 0;j < COL;j++) {
			if (arr[i][j] == -1) {
				ci = i;
				cj = j;
			}
			else continue;
			if (ci == x1 || cj == y1) {
				if (Erase_xy(x1, ci, y1, cj) && Erase_xy(x2, ci, y2, cj)) return true;
			}
			if (ci == x2 || cj == y2) {
				if (Erase_xy(x1, ci, x2, cj) && Erase_xy(x1, ci, x2, cj)) return true;
			}
		}
	}
	return false;
}

int main()
{
	//mciSendString("open res/music.mp3",NULL,0,NULL);
	//mciSendString("play res/music.mp3 repeat", NULL, 0, NULL);//play open pause resume close 
															//repeat alias(起别名)
	initgraph(WIDTH,LENGTH,1);	// 创建绘图窗口，大小为 640x480 像素
	IMAGE img,imgbk,p[16],imgwin;
	loadimage(&img,"res/start.png",100,100);
	loadimage(&imgbk,"res/bkimg.png", WIDTH,LENGTH);
	loadimage(&imgwin, "res/success.png", WIDTH, LENGTH);
	putimage(WIDTH/2-50,LENGTH/2-50,&img);
	MOUSEMSG msg;

	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN&&msg.x>WIDTH/2-50&&msg.x<WIDTH/2+50&&msg.y>LENGTH/2-50&&msg.y<LENGTH/2+50) {
			putimage(0, 0, &imgbk);
			break;
		}
	}



	for (i = 0;i <16;i++) {
		char buff[50];
		sprintf(buff, "res/%d.png", i + 1);
		loadimage(&p[i], buff, XS, XS);
	}

	srand(time(NULL));

	for (i = 0;i < ROW/2;i++) {
		for (j = 0;j < COL;j++) {
			arr[i][j] = rand() % 16;
		}
	}
	for (i = ROW/2;i < ROW;i++) {
		for (j = 0;j < COL;j++) {
			arr[i][j] = arr[i - ROW / 2][COL-j-1];
		}
	}
	for (i = 0;i < 1000;i++) {
		int x1, x2, y1, y2,tmp;
		x1 = rand() % COL;
		x2 = rand() % COL;
		y1 = rand() % ROW;
		y2 = rand() % ROW;
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;

	}
	for (i = 0;i < ROW;i++) {
		for (j = 0;j < COL;j++) {
			putimage(x + j * (XS+GAP), y + i * (XS+GAP), &p[arr[i][j]]);
		}
	}
	int num = ROW * COL;
	int key = 0;
	int x1, x2, y1, y2;
	//mciSendString("open res/disappear.mp3", NULL, 0, NULL);
	while (num) {
		MOUSEMSG msg1,msg2;
		if (key==0) {
			msg1 = userClick();
			x1 = (msg1.y - y) / (GAP + XS);
			y1 = msg1.x / (GAP + XS);
			key=1;
		}
		if (key == 1) {
			msg2 = userClick();
			x2 = (msg2.y - y) / (GAP + XS);
			y2 = msg2.x / (GAP + XS);
		}

		if (arr[x1][y1] == arr[x2][y2]&&(!(x1==x2&&y1==y2))&&(Erase_xy(x1,x2,y1,y2)||Erase_else(x1,x2,y1,y2))) {
			//PlaySound("res/disappear.wav", NULL, SND_FILENAME|SND_ALIAS);
			arr[x1][y1] = -1;
			arr[x2][y2] = -1;
			num -= 2;
			putimage(0, 0, &imgbk);
			for (i = 0;i < ROW;i++) {
				for (j = 0;j < COL;j++) {

					if (arr[i][j] != -1) {
						putimage(x + j * (XS + GAP), y + i * (XS + GAP), &p[arr[i][j]]);
					}
				}
			}
			key = 0;
		}
		else {
			x1 = x2;
			y1 = y2;
			key = 1;
		}
		
	}
	putimage(0, 0, &imgwin);
	mciSendString("open res/disappear.wav", NULL, 0, NULL);
	if (num == 0) {
		mciSendString("play res/win.mp3", NULL, 0, NULL);
		MessageBox(NULL, "win", "end", MB_OK|MB_OKCANCEL);
	}


	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}
