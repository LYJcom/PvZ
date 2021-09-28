#pragma once

#include<string>
using namespace std;

#include"ui.h"

class Game;
class Grid;

/* ����ֲ��Ļ��� */
class Plant 
{
protected:
	//ֲ����
	string name;
	//��������
	int x, y;

	//ֲ���;öȣ�Ĭ�϶���300��
	int HP;
	int maxHP;

	//�趨ֲ����
	void Setting(const string& str, int hp = 300, int colorID = NONE_COLOR)
	{
		name = str;
		maxHP = HP = hp;
		nameColor = colorID;
	}

	friend class Plot;
	friend class Map;
	friend class Pole_Zombie;
public:

	//����ֲ������
	const string& getName() const { return name; }
	//�趨��������
	void setXY(int ix, int iy) 
	{
		x = ix;
		y = iy;
	}
	//������Ϊ��Ĭ���ޣ����磺�����㶹����������
	virtual void Special(Game& nowGame) {}
	//���ֲ����
	virtual void printName();
	//ֲ��������ɫ
	int nameColor;
	//���ʣ������ֵ
	virtual void printLife();
};


/* ��������ֲ�� */

//�㶹����
class PeaShooter :public Plant 
{
private:
	int speed; //�����ٶȣ����ʱ�䣩
	int cnt;

public:
	PeaShooter() 
	{
		Setting("�㶹����", 300, PEASHOOTER_COLOR);
		speed = 14; //1.4��
		cnt = 0;
	}
	void Special(Game& game);
};

//���տ�
class SunFlower :public Plant 
{
private:
	int speed; //����������ٶȣ�ʱ������
	int cnt;

public:
	SunFlower() 
	{
		Setting("���տ�", 300, SUNFLOWER_COLOR);
		speed = 30; //���Σ�3��һ������
		cnt = 0;
	}
	void Special(Game& game);
};

//˫������
class Repeater :public Plant
{
private:
	int speed; //�����ٶȣ����ʱ�䣩
	int cnt;

public:
	Repeater()
	{
		Setting("˫������", 300, PEASHOOTER_COLOR);
		speed = 7; //0.7��
		cnt = 0;
	}
	void Special(Game& game);
};

//���ǽ
class WallNut :public Plant
{
public:
	WallNut()
	{
		Setting("�� �� ǽ", 4000, SUNFLOWER_COLOR);
	}
	void printName();
};

//�߼��
class Tall_nut :public Plant
{
public:
	Tall_nut()
	{
		Setting(" �߼�� ", 8000, SUNFLOWER_COLOR);
	}
	void printName();
};

//�Ϲ�ͷ
class PumpKin :public Plant
{
public:
	PumpKin()
	{
		Setting("�� �� ͷ", 4000, SUNFLOWER_COLOR);
	}
	void printName();
};

//�ѹ�
class Squash :public Plant 
{
	//������
	int damage;
	//��ֲʱ���Ӻ�ſ�ʼ����Ч��
	int speed;
	//ʱ�����
	int counter;
	bool flag;//������־

public:
	Squash() 
	{
		Setting("�ѹ�"); 
		nameColor = PEASHOOTER_COLOR;
		speed = 8; 
		counter = 0; 
		flag = false;
		damage = 1800;
	}
	void Special(Game& nowGame);
};

//ӣ��ը��
class CherryBomb :public Plant 
{
	//��ֲ�������ſ�ʼ����Ч��
	int speed;
	//ʱ�����
	int counter;
	//������
	int damage;

public:
	CherryBomb() 
	{
		Setting("ӣ��ը��", 1000); 
		nameColor = CHERRY_BOMB_COLOR;
		speed = 5; 
		counter = 0; 
		damage = 1800;
	}
	void Special(Game& game);
};

//����
class Garlic :public Plant 
{
public:
	Garlic() 
	{
		Setting("���� ", 400); nameColor = GARLIC_COLOR;
	}
	void printName();
	void Special(Game& game);
};

//��������
class SnowPea :public Plant 
{
	//�����ٶ�
	int speed;
	//ʱ�Ӽ���
	int cnt;
public:
	SnowPea() 
	{
		Setting("��������");
		nameColor = SNOW_PEA_COLOR;
		speed = 14;
		cnt = 0;
	}
	void Special(Game& game);
};