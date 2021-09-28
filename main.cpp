#define _CRT_SECURE_NO_WARNINGS
#include"Game.h"

int main() 
{
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", WINDOWS_WIDTH, WINDOWS_HEIGHT);
	system(cmd); //设置窗口宽度和高度
	HideCursor();
	srand((unsigned int)time(NULL));
	Game PvZ;
	PvZ.init();
	PvZ.start();
	return 0;
}
