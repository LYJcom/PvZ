#pragma once
#include"Zombie.h"
#include<vector>
using namespace std;

class Map;
class Bullet
{
public:
	int x, y; //子弹当前位置
	int speed; //子弹移动速度
	int damage; //造成伤害

	int cnt;

public:
	Bullet();
	
	void setXY(int dx, int dy); //计算并设置子弹的起始坐标（(dx,dy)位置的植物发射子弹）
	
	virtual void move(Map& map); //向前移动

	virtual void ifHit(Map& map);
	
	virtual void paint(); //绘制子弹

	virtual void hitZombie(Zombie* z); //对僵尸造成伤害
	
	bool hit; //是否击中
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