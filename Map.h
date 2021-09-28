#pragma once
#include"ui.h"
#include "Plant.h"
#include"Zombie.h"
#include<vector>
using namespace std;

class Game;
class Zombie;
class Plot
{
	//格子左上角的坐标
	int dx, dy;
	
	Plant* plant; //此格子中的植物
	Plant* pumpkin; //此格中的南瓜头

	vector<Zombie*> zombies;
	
	/*其他辅助信息*/
	bool selected;//是否选中

	bool remove_selected; //铲子选中
	
	bool refresh;//用于标记是否需要刷新显示

	void setRefresh() 
	{ 
		refresh = true; 
	}

public:
	Plot() 
	{
		plant = nullptr; 
		selected = false; 
		refresh = false;
	}
	
	void setXY(int x, int y);//根据格子的坐标来设定dx,dy
	
	void paint();//绘制格子中的显示内容
	
	bool setPlant(Plant* p);//设定植物

	bool setPumpKin(Plant* p); //种植南瓜头

	bool PumpKin_exist()
	{
		return pumpkin != nullptr;
	}
	
	void remove_Plant() //清空植物
	{
		delete plant; 
		plant = nullptr; 
		refresh = true; 
	}

	void remove_PumpKin() //去除南瓜头
	{
		delete pumpkin;
		pumpkin = nullptr;
		refresh = true;
	}

	void delete_Plants()
	{
		if (plant != nullptr)
		{
			delete plant;
			plant = nullptr;
			refresh = true;
		}
		if(pumpkin != nullptr)
		{
			delete pumpkin;
			pumpkin = nullptr;
			refresh = true;
		}
	}

	void addZombie(Zombie* iZombie);

	void deleteZombie(Zombie* iZombie);

	void hitZombies(int damage);

	void Plant_eaten(int damage); //植物被吃

	void PumpKin_eaten(int damage); //南瓜头被吃
	
	void eating(); //判断僵尸是否吃植物

	void setSelected(int state) //设定选中状态
	{
		if (state == 1)
			selected = true;
		else
			remove_selected = true;
		refresh = true; 
	}
	void setUnSelected() //设定非选中状态
	{
		selected = false; 

		remove_selected = false;
		refresh = true; 
	}

	~Plot() 
	{
		delete plant;
		delete pumpkin;
	}

	friend class Map;
	friend class Store;
	friend class PeaShooter;
	friend class SnowPea;
	friend class Repeater;
	friend class Squash;
	friend class CherryBomb;
	friend class Garlic;
	friend class Bullet;
	friend class BasketBall;
	friend class Game;
	friend class Zombies;
	friend class Pole_Zombie;
	friend class Catapult_Zombie;
	friend class Box_Zombie;
};

class Map
{
	Plot plot[PLOT_NUM_X + 1][PLOT_NUM_Y];
public:
	void init();

	void paintPlotLine(); //网格线（草地块的边界）的绘制

	bool allPlot(Game& game); //遍历所有地块

	bool setPlant(int ix, int iy, int type); //种植植物

	bool setPumpKin(int ix, int iy); //种植南瓜头

	void refresh(); //刷新显示

	friend class Game;
	friend class PeaShooter;
	friend class SnowPea;
	friend class Repeater;
	friend class Squash;
	friend class CherryBomb;
	friend class Garlic;
	friend class Bullet;
	friend class BasketBall;
	friend class Zombie;
	friend class Zombies;
	friend class Pole_Zombie;
	friend class Catapult_Zombie;
	friend class Box_Zombie;
};