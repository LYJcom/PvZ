#pragma once
#include"Color.h"
using namespace std;

// ���ù��λ��
void Cursor(const int x, const int y);

// ���ع��
void HideCursor();

// ����ɫ���ı������Ĭ��Ϊ�ڵװ���
void Print(const string& str, int colorID = NONE_COLOR);
void Print(int num, int colorID = NONE_COLOR);
