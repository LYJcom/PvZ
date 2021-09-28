#pragma once
#include"ui.h"
#include<string>
using namespace std;

class Game;
class Store;
class Map;

//�����̵�չʾ��ֲ�￨��
class Card 
{
	int dx;//��������
	int ID; //ֲ����
	string name; //ֲ������
	int price; //�۸�
	int cd; //��ȴʱ��
	bool selected; //�Ƿ�ѡ��

	int cnt; //ʱ�����

	friend class Store;
public:
	//�趨����
	void set(int i, const string& n, int p, int c) 
	{
		ID = i;
		dx = i;
		if (i == -1)
			dx = 9;
		name = n;
		price = p;
		cd = c ; //(c/10)���cdʱ��
		cnt = cd;
		selected = false;
	}
	//���ֲ�ﹺ����Ϣ�����֡��۸��Լ���ȴ���ȣ�
	void print();
	
	void setSelect() //ѡ��
	{ 
		selected = true; 
		print(); 
	}
	void setUnSelect() //��ѡ��
	{
		selected = false; 
		print();
	}
	//��ȴ
	void cooling();
	//�Ƿ���ȴ����
	bool coolingDone();
};

class Store
{
	Card plants[PLANT_TYPE_MAX];

	int sun; //��������
	int speed; //��Ȼ����������ٶ�

	int cnt; //ʱ�����
public:
	Store() 
	{
		plants[0].set(0, "���տ�  ", 50, 75);
		plants[1].set(1, "�㶹����", 100, 75);
		plants[2].set(2, "���ǽ", 50, 300);
		plants[3].set(3, "˫������", 200, 75);
		plants[4].set(4, "�߼��", 125, 300);
		plants[5].set(5, "�ѹ�", 50, 200);
		plants[6].set(6, "ӣ��ը��", 150, 200);
		plants[7].set(7, "�Ϲ�ͷ", 125, 300);
		plants[8].set(8, "��������", 175, 75);
		plants[9].set(-1, "����", 50, 75);
	}

	void init();
	
	void paintCardLine(); //��Ƭ����
	
	void refreshSun(); //ˢ���������������

	void addSun(int _sun = 25) 
	{ 
		sun += _sun; 
		refreshSun(); 
	}
	
	bool pay(int choice, int x, int y, Map& map);

	void run();

	//���������ȴ�����ڲ��ԣ�
	void renew();

	friend class Game;
};

