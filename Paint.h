#pragma once
#include"Color.h"
using namespace std;

// 设置光标位置
void Cursor(const int x, const int y);

// 隐藏光标
void HideCursor();

// 带颜色的文本输出，默认为黑底白字
void Print(const string& str, int colorID = NONE_COLOR);
void Print(int num, int colorID = NONE_COLOR);
