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
	//�������Ͻǵ�����
	int dx, dy;
	
	Plant* plant; //�˸����е�ֲ��
	Plant* pumpkin; //�˸��е��Ϲ�ͷ

	vector<Zombie*> zombies;
	
	/*����������Ϣ*/
	bool selected;//�Ƿ�ѡ��

	bool remove_selected; //����ѡ��
	
	bool refresh;//���ڱ���Ƿ���Ҫˢ����ʾ

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
	
	void setXY(int x, int y);//���ݸ��ӵ��������趨dx,dy
	
	void paint();//���Ƹ����е���ʾ����
	
	bool setPlant(Plant* p);//�趨ֲ��

	bool setPumpKin(Plant* p); //��ֲ�Ϲ�ͷ

	bool PumpKin_exist()
	{
		return pumpkin != nullptr;
	}
	
	void remove_Plant() //���ֲ��
	{
		delete plant; 
		plant = nullptr; 
		refresh = true; 
	}

	void remove_PumpKin() //ȥ���Ϲ�ͷ
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

	void Plant_eaten(int damage); //ֲ�ﱻ��

	void PumpKin_eaten(int damage); //�Ϲ�ͷ����
	
	void eating(); //�жϽ�ʬ�Ƿ��ֲ��

	void setSelected(int state) //�趨ѡ��״̬
	{
		if (state == 1)
			selected = true;
		else
			remove_selected = true;
		refresh = true; 
	}
	void setUnSelected() //�趨��ѡ��״̬
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

	void paintPlotLine(); //�����ߣ��ݵؿ�ı߽磩�Ļ���

	bool allPlot(Game& game); //�������еؿ�

	bool setPlant(int ix, int iy, int type); //��ֲֲ��

	bool setPumpKin(int ix, int iy); //��ֲ�Ϲ�ͷ

	void refresh(); //ˢ����ʾ

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