#pragma once
#include"Zombie.h"
#include<vector>
using namespace std;

class Map;
class Bullet
{
public:
	int x, y; //�ӵ���ǰλ��
	int speed; //�ӵ��ƶ��ٶ�
	int damage; //����˺�

	int cnt;

public:
	Bullet();
	
	void setXY(int dx, int dy); //���㲢�����ӵ�����ʼ���꣨(dx,dy)λ�õ�ֲ�﷢���ӵ���
	
	virtual void move(Map& map); //��ǰ�ƶ�

	virtual void ifHit(Map& map);
	
	virtual void paint(); //�����ӵ�

	virtual void hitZombie(Zombie* z); //�Խ�ʬ����˺�
	
	bool hit; //�Ƿ����
};

class SnowBullet :public Bullet 
{
	void hitZombie(Zombie* z);
	void paint();
};

class BasketBall :public Bullet
{
public:
	BasketBall()
	{
		speed = 1;
		damage = 20;
		cnt = 0;
		hit = false;
	}
	void paint();
	void move(Map& map);
	void ifHit(Map& map){}
};