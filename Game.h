#pragma once
#include "Map.h"
#include "Store.h"
#include"Bullet.h"
#include"Zombie.h"
#include<list>

using namespace std;

class Plant;

class Game 
{
private:
	Map map;
	Store store;
	Zombies zombies;

	list<Bullet*> bullets; //子弹队列

	int state; //状态：正常、购买状态、铲除植物、游戏暂停
	enum GAME_STATE { PROCEED, STORE, REMOVE, PAUSE };

	void remove(); //铲除植物

	void shopping(); //购买植物
	int planting_type; //当前准备种植的植物类型

	int make_speed; //僵尸产生速度
	int make_cnt;

	int score; //得分
	int x, y; //当前焦点位置

	void Unselected(); //关闭选择

	void remove_Plant(int ix, int iy); //铲除某个位置的植物
	void remove_Plants(int ix, int iy); //铲除某个位置的所有植物

	void moveBullet(); //子弹移动

	void ifBulletHit(); //子弹击中僵尸的边界情况判断

	void printBullet(); //显示子弹

	void Pause_Display(); // 暂停键显示
	void Pause_Hide(); //暂停键隐藏
	
	void Help();//帮助信息的输出
	bool Help_refresh; //切换状态提示

	void pause(); //暂停
	
	void gameover(); //游戏结束

	void gameExit(); //主动退出游戏

public:
	void init();//游戏初始化
	
	void start();//游戏主体

	friend class SunFlower;
	friend class PeaShooter;
	friend class SnowPea;
	friend class Repeater;
	friend class Squash;
	friend class CherryBomb;
	friend class Garlic;
	friend class Catapult_Zombie;
	friend class Box_Zombie;
	friend class Zombies;
};

