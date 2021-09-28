#pragma once
#include"ui.h"
#include<string>
#include<list>
using namespace std;

class Map;
class Game;

//普通僵尸
class Zombie
{
protected:
	int x, y; //所在地块坐标

	int HP; //当前血量
	int maxHP; //最大血量（270）

	string name; //僵尸名

	int speed; //移动速度（移动一格所需时间）

	int cnt; //用于移动的计数

	int damage; //攻击力（单位时间造成伤害）

	int score; //击杀得分（50）

	bool eating; //标记处于吃植物的状态

	bool freezing; //减速效果
	int freezing_time; //减速效果持续时间
	int freezing_cnt;

	bool garlic_effect; //是否刚吃了大蒜
	int move_cnt;
	int move_time;

protected:
	//属性参数设定
	void Setting(const string n, int s = 50, int hp = 250, int ten_speed = 75, int d = 100)
	{
		name = n;
		score = s;
		maxHP = HP = hp;
		speed = ten_speed; //速度：（ten_speed/10）秒移动一格
		damage = d / 10; //攻击力：d点伤害/秒
	}

	//输出僵尸名字
	virtual void printName();
	//僵尸额外信息
	virtual void printExtra(){}

public:
	Zombie()
	{
		cnt = 0; 
		eating = false; 
		garlic_effect = false;
		move_time = 8;
		move_cnt = 0;
		freezing = false; 
		freezing_cnt = 0;
		freezing_time = 80;
		Setting("  僵尸  ");
	}
	
	const string& getName() const //返回僵尸名字
	{ 
		return name;
	}

	void setXY(int ix, int iy) //设定起始位置 
	{
		x = ix; 
		y = iy; 
	}

	virtual void setFreezing()
	{
		freezing = true; 
		freezing_cnt = 0; 
	};

	void SetGarlic()
	{
		if (!garlic_effect)
		{
			garlic_effect = true;
			move_cnt = 0;
		}
	}
	void ClearGarlic()
	{
		garlic_effect = false;
	}
	
	virtual bool move(Map& map); //僵尸行动（包括位移、吃植物等动作），返回值代表是否攻破
	virtual bool move(Game& game) { return false; };

	virtual void hit(int damage) //被攻击
	{
		HP -= damage;
	}

	friend class Zombies;
	friend class Game;
	friend class Bullet;
	friend class Plot;
};

class Zombies
{
private:
	list<Zombie*> zombies;

	void addZombie(int x, int y, int type, Game& game);
	void makeZombie(Game& game);
	bool moveZombie(Game& game);
	void clearZombie(Game& game);

public:
	bool run(Game& game);
	~Zombies()
	{
		for (auto& var : zombies) 
		{
			delete var;
		}
	}
};

class ConeheadZombie :public Zombie
{
public:
	ConeheadZombie() 
	{
		Setting("路障僵尸", 75, 700);
	}
};

class Newspaper_Zombie :public Zombie 
{
	//临界点
	int transHP;
	//报纸没了后的速度 1.2秒/格
	int speed_Plus = 12 * 1000 / 10 / TIME;
	//报纸没了后的攻击力
	int attack_Plus = 200;
public:
	Newspaper_Zombie() 
	{
		Setting("读报僵尸", 125, 300); 
		transHP = 200; 
	}
	void setFreezing()
	{
		if (HP <= transHP) 
		{
			freezing = true;
			freezing_cnt = 0;
		}
	}
	void printExtra();
	//重写扣血函数（报纸没了要加速）
	void hit(int idamage);
	
};

class Pole_Zombie :public Zombie 
{
	//临界点：是否有撑杆
	bool hasPole;
	//跳完之后的速度 4.5秒/格
	int speed2 = 45 * 1000 / 10 / TIME;
public:
	Pole_Zombie() 
	{
		Setting("撑杆僵尸", 100, 430, 20); 
		hasPole = true; 
	}
	void printExtra();
	bool move(Map& map);
};

class Catapult_Zombie :public Zombie
{
	int num; //篮球数
	int cnt_shoot, speed_shoot;
	bool First_three_plots;
	bool none_basketball;
public:
	Catapult_Zombie() 
	{
		Setting("投石车僵尸", 500, 850, 25); 
		num = 20; 
		none_basketball = false;  
		First_three_plots = true;
		cnt_shoot = 0;
		speed_shoot = 14;
	}
	void setFreezing() {}
	void printName();
	bool move(Game& game);
};

class Box_Zombie :public Zombie
{
	//一定时间后触发概率自爆
	int bomb_time;
	//自爆时间计数
	int bomb_counter;
	//是否启动爆炸
	bool bomb_flag;
public:
	Box_Zombie()
	{
		Setting("小丑僵尸", 250, 800, 22);
		bomb_time = 30;
		bomb_counter = 0;
		bomb_flag = false;
	}
	void printName();
	bool move(Map& map);
};
