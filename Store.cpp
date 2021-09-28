#include "Store.h"
#include "Map.h"

#include<conio.h>
#include<iostream>
using namespace std;

void Card::print()
{
	//�ο�λ���趨
	int Dx = 2 + dx * (CARD_WIDTH + 1);
	//int Dy = STORE_UP_BOUND + STORE_HEIGHT - 4; //��һ��
	int Dy = 4;

	Cursor(Dx+2, Dy+4);
	string str(6, ' ');
	cout << str;
	Cursor(Dx+4, Dy);
	Print(ID + 1, SUN_AND_SCORE_COLOR);
	Cursor(Dx, Dy+2);
	if (selected)
	{
		Print(name, SELECTED_COLOR);
	}
	else
	{
		Print(name, SUN_AND_SCORE_COLOR);
	}
	Cursor(Dx+1, Dy+3);
	Print("-", SUN_AND_SCORE_COLOR);
	Print(price, SUN_AND_SCORE_COLOR);
	Print("$", SUN_AND_SCORE_COLOR);
	if (cnt < cd) 
	{
		Cursor(Dx+2, Dy+4);
		Print("(", COOLING);
		Print(cnt * 100 / cd, COOLING);
		Print("%)", COOLING);
		//cout << "(" << cnt * 100 / cd << "%)";
	}
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NONE_COLOR);
}

void Card::cooling()
{
	if (cnt >= cd) return; //������ȴ
	else 
	{
		cnt++;
		print();
	}
}

bool Card::coolingDone()
{
	return cnt >= cd;
}

void Store::init()
{
	sun = 5000; //��ʼ����
	
	cnt = 0;

	speed = 60; //ÿ6����������


	//�̶������UI����
	//Cursor(2, STORE_UP_BOUND + 1);
	Cursor(2, 1);
	Print("���̵꡿", SUN_AND_SCORE_COLOR);
	//Cursor(RIGHT_LINE_X, STORE_UP_BOUND + 1);
	Cursor(RIGHT_LINE_X, 1);
	Print("|", SUN_AND_SCORE_COLOR);
	//Cursor(0, STORE_UP_BOUND + 2);
	Cursor(0, 2);
	string str(WINDOWS_WIDTH, '-');
	Print(str, SUN_AND_SCORE_COLOR);


	//�ɱ��UI���ֵ��״����
	refreshSun();
	for (int i = 0; i < PLANT_TYPE_MAX; i++)
	{
		plants[i].print();
	}
}

void Store::refreshSun()
{
	//�����
	//Cursor(RIGHT_LINE_X - 17, STORE_UP_BOUND + 1);
	Cursor(RIGHT_LINE_X - 17, 1);
	string str(16, ' ');
	cout << str;
	//���������
	//Cursor(RIGHT_LINE_X - 17, STORE_UP_BOUND + 1);
	Cursor(RIGHT_LINE_X - 17, 1);
	Print("���⣺", SUN_AND_SCORE_COLOR);
	Print(sun, SUN_AND_SCORE_COLOR);
	Print(" $", SUN_AND_SCORE_COLOR);
}

bool Store::pay(int choice, int x, int y, Map& map)
{
	if (sun >= plants[choice].price && plants[choice].coolingDone())
	{
		if (choice == 7 && map.setPumpKin(x, y))
		{
			sun -= plants[choice].price;
			refreshSun();
			plants[choice].cnt = 0;
			return true;
		}
		else if (choice != 7 && map.setPlant(x, y, choice)) 
		{
			sun -= plants[choice].price;
			refreshSun();
			plants[choice].cnt = 0;
			return true;
		}
	}
	return false;
}

void Store::run() 
{
	paintCardLine();
	cnt++;
	if (cnt >= speed) 
	{
		cnt = 0;
		addSun();
	}

	//��ȴֲ��
	for (int i = 0; i < PLANT_TYPE_MAX; i++) 
	{
		plants[i].cooling();
	}
}

void Store::paintCardLine()
{
	/*����ֲ������ʱ�����*/
	string str((PLANT_TYPE_MAX) * CARD_WIDTH + 9, '-');

	Cursor(1, 3);
	Print(str, SUN_AND_SCORE_COLOR);
	for (int j = 1; j <= CARD_HEIGHT; j++)
	{
		for (int k = 0; k <= PLANT_TYPE_MAX; k++)
		{
			Cursor(k * (CARD_WIDTH + 1), 3 + j);
			Print("|", SUN_AND_SCORE_COLOR);
		}
	}
	Cursor(1, CARD_HEIGHT + 1 + 3);
	Print(str, SUN_AND_SCORE_COLOR);
}

void Store::renew()
{
	for (int i = 0; i < PLANT_TYPE_MAX; i++)
	{
		plants[i].cnt = plants[i].cd;
		plants[i].print();
	}
}