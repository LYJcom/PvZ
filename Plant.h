#pragma once

#include<string>
using namespace std;

#include"ui.h"

class Game;
class Grid;

/* 所有植物的基类 */
class Plant 
{
protected:
	//植物名
	string name;
	//所在网格
	int x, y;

	//植物耐久度（默认都是300）
	int HP;
	int maxHP;

	//设定植物名
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

	//返回植物名字
	const string& getName() const { return name; }
	//设定所在网格
	void setXY(int ix, int iy) 
	{
		x = ix;
		y = iy;
	}
	//特殊行为（默认无），如：发射豌豆、产生阳光
	virtual void Special(Game& nowGame) {}
	//输出植物名
	virtual void printName();
	//植物名的颜色
	int nameColor;
	//输出剩余生命值
	virtual void printLife();
};


/* 各类具体的植物 */

//豌豆射手
class PeaShooter :public Plant 
{
private:
	int speed; //发射速度（间隔时间）
	int cnt;

public:
	PeaShooter() 
	{
		Setting("豌豆射手", 300, PEASHOOTER_COLOR);
		speed = 14; //1.4秒
		cnt = 0;
	}
	void Special(Game& game);
};

//向日葵
class SunFlower :public Plant 
{
private:
	int speed; //产生阳光的速度（时间间隔）
	int cnt;

public:
	SunFlower() 
	{
		Setting("向日葵", 300, SUNFLOWER_COLOR);
		speed = 30; //初次：3秒一次阳光
		cnt = 0;
	}
	void Special(Game& game);
};

//双发射手
class Repeater :public Plant
{
private:
	int speed; //发射速度（间隔时间）
	int cnt;

public:
	Repeater()
	{
		Setting("双发射手", 300, PEASHOOTER_COLOR);
		speed = 7; //0.7秒
		cnt = 0;
	}
	void Special(Game& game);
};

//坚果墙
class WallNut :public Plant
{
public:
	WallNut()
	{
		Setting("坚 果 墙", 4000, SUNFLOWER_COLOR);
	}
	void printName();
};

//高坚果
class Tall_nut :public Plant
{
public:
	Tall_nut()
	{
		Setting(" 高坚果 ", 8000, SUNFLOWER_COLOR);
	}
	void printName();
};

//南瓜头
class PumpKin :public Plant
{
public:
	PumpKin()
	{
		Setting("南 瓜 头", 4000, SUNFLOWER_COLOR);
	}
	void printName();
};

//窝瓜
class Squash :public Plant 
{
	//攻击力
	int damage;
	//种植时间延后才开始产生效果
	int speed;
	//时间计数
	int counter;
	bool flag;//计数标志

public:
	Squash() 
	{
		Setting("窝瓜"); 
		nameColor = PEASHOOTER_COLOR;
		speed = 8; 
		counter = 0; 
		flag = false;
		damage = 1800;
	}
	void Special(Game& nowGame);
};

//樱桃炸弹
class CherryBomb :public Plant 
{
	//种植多少秒后才开始产生效果
	int speed;
	//时间计数
	int counter;
	//攻击力
	int damage;

public:
	CherryBomb() 
	{
		Setting("樱桃炸弹", 1000); 
		nameColor = CHERRY_BOMB_COLOR;
		speed = 5; 
		counter = 0; 
		damage = 1800;
	}
	void Special(Game& game);
};

//大蒜
class Garlic :public Plant 
{
public:
	Garlic() 
	{
		Setting("大蒜 ", 400); nameColor = GARLIC_COLOR;
	}
	void printName();
	void Special(Game& game);
};

//寒冰射手
class SnowPea :public Plant 
{
	//发射速度
	int speed;
	//时钟计数
	int cnt;
public:
	SnowPea() 
	{
		Setting("寒冰射手");
		nameColor = SNOW_PEA_COLOR;
		speed = 14;
		cnt = 0;
	}
	void Special(Game& game);
};