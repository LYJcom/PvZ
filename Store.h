#pragma once
#include"ui.h"
#include<string>
using namespace std;

class Game;
class Store;
class Map;

//用于商店展示的植物卡牌
class Card 
{
	int dx;//卡牌坐标
	int ID; //植物编号
	string name; //植物名字
	int price; //价格
	int cd; //冷却时间
	bool selected; //是否选中

	int cnt; //时间计数

	friend class Store;
public:
	//设定参数
	void set(int i, const string& n, int p, int c) 
	{
		ID = i;
		dx = i;
		if (i == -1)
			dx = 9;
		name = n;
		price = p;
		cd = c ; //(c/10)秒的cd时间
		cnt = cd;
		selected = false;
	}
	//输出植物购买信息（名字、价格，以及冷却进度）
	void print();
	
	void setSelect() //选中
	{ 
		selected = true; 
		print(); 
	}
	void setUnSelect() //非选中
	{
		selected = false; 
		print();
	}
	//冷却
	void cooling();
	//是否冷却结束
	bool coolingDone();
};

class Store
{
	Card plants[PLANT_TYPE_MAX];

	int sun; //阳光数量
	int speed; //自然生产阳光的速度

	int cnt; //时间计数
public:
	Store() 
	{
		plants[0].set(0, "向日葵  ", 50, 75);
		plants[1].set(1, "豌豆射手", 100, 75);
		plants[2].set(2, "坚果墙", 50, 300);
		plants[3].set(3, "双发射手", 200, 75);
		plants[4].set(4, "高坚果", 125, 300);
		plants[5].set(5, "窝瓜", 50, 200);
		plants[6].set(6, "樱桃炸弹", 150, 200);
		plants[7].set(7, "南瓜头", 125, 300);
		plants[8].set(8, "寒冰射手", 175, 75);
		plants[9].set(-1, "大蒜", 50, 75);
	}

	void init();
	
	void paintCardLine(); //卡片边线
	
	void refreshSun(); //刷新阳光数量的输出

	void addSun(int _sun = 25) 
	{ 
		sun += _sun; 
		refreshSun(); 
	}
	
	bool pay(int choice, int x, int y, Map& map);

	void run();

	//完成所有冷却（便于测试）
	void renew();

	friend class Game;
};

