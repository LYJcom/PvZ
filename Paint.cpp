#include"Paint.h"
using namespace std;

//设置光标位置
void Cursor(const int x, const int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

// 带颜色的文本输出，默认为黑底白字
void Print(const string& str, int colorID)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID); //设置文本颜色
	cout << str;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NONE_COLOR); //输出结束后设置回默认色
}

void Print(int num, int colorID)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
	cout << num;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NONE_COLOR); //输出结束后设置回默认色
}