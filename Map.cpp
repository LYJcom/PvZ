#include "Map.h"
#include<iostream>
using namespace std;

void Map::init()
{
	system("cls");
	//网格线（草地块的边界）的绘制
	paintPlotLine();
	//每个格子初始化
	for (int i = 0; i < PLOT_NUM_X + 1; i++)
	{
		for (int j = 0; j < PLOT_NUM_Y; j++) 
		{
			plot[i][j].setXY(i, j);
		}
	}
}

void Plot::setXY(int x, int y)
{
	dx = x * (PLOT_WIDTH + 1) + 1;
	//dy = y * (PLOT_HEIGHT + 1) + 1;
	dy = y * (PLOT_HEIGHT + 1) + 1 + 10;
}

void Map::paintPlotLine()
{
	int Map_Plot_Width = (PLOT_WIDTH + 1) * PLOT_NUM_X + 1;
	int Map_Ground_Width = WINDOWS_WIDTH - Map_Plot_Width;

	//网格线（草地块的边界）的绘制
	for (int i = 0; i < PLOT_NUM_Y; i++)
	{
		string str1(Map_Plot_Width, '#');
		string str2(Map_Ground_Width, '#');
		//Cursor(0, i * (PLOT_HEIGHT + 1));
		Cursor(0, i * (PLOT_HEIGHT + 1) + 10);
		Print(str1, GRASS_COLOR);
		Print(str2, GROUND_COLOR);

		for (int j = 1; j <= PLOT_HEIGHT; j++)
		{
			for (int k = 0; k <= PLOT_NUM_X; k++)
			{
				//Cursor(k * (PLOT_WIDTH + 1), i * (PLOT_HEIGHT + 1) + j);
				Cursor(k * (PLOT_WIDTH + 1), i * (PLOT_HEIGHT + 1) + j + 10);
				Print("#", GRASS_COLOR);
			}
		}
	}
	string str1(Map_Plot_Width, '#');
	string str2(Map_Ground_Width, '#');
	//Cursor(0, PLOT_NUM_Y * (PLOT_HEIGHT + 1));
	Cursor(0, PLOT_NUM_Y * (PLOT_HEIGHT + 1) + 10);
	Print(str1, GRASS_COLOR);
	Print(str2, GROUND_COLOR);
}

void Plot::paint()
{
	refresh = false;

	//先清空整个格子
	string str(PLOT_WIDTH, ' ');
	for (int i = 0; i < PLOT_HEIGHT; i++) 
	{
		Cursor(dx, dy + i);
		Print(str);
	}

	
	if (selected) //选中状态 输出选择框
	{
		string str(PLOT_WIDTH - 2, '-'); //长度内嵌格子的横线
		Cursor(dx, dy);
		//Print("+" + str + "+");
		cout << "+" << str << "+";
		for (int i = 1; i < PLOT_HEIGHT - 1; i++) //打印两侧内嵌格子的竖线
		{
			Cursor(dx, dy + i);
			//Print("|");
			cout << "|";
			Cursor(dx + PLOT_WIDTH - 1, dy + i);
			//Print("|");
			cout << "|";
		}
		Cursor(dx, dy + PLOT_HEIGHT - 1);
		//Print("+" + str + "+");
		cout << "+" << str << "+";
	}

	if(remove_selected) //铲除选中状态 输出选择框
	{
		string str(PLOT_WIDTH - 2, '-'); //长度内嵌格子的横线
		Cursor(dx, dy);
		Print("x" + str + "x", REMOVE_COLOR);
		for (int i = 1; i < PLOT_HEIGHT - 1; i++) //打印两侧内嵌格子的竖线
		{
			Cursor(dx, dy + i);
			Print("|", REMOVE_COLOR);
			Cursor(dx + PLOT_WIDTH - 1, dy + i);
			Print("|", REMOVE_COLOR);
		}
		Cursor(dx, dy + PLOT_HEIGHT - 1);
		Print("x" + str + "x", REMOVE_COLOR);
	}

	//输出植物、僵尸等信息
	if (plant != nullptr && zombies.size() == 0) 
	{
		//植物名
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		plant->printName();
		//植物剩余HP
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2 + 1);
		plant->printLife();
	}
	else if (plant != nullptr && zombies.size() != 0) 
	{
		//植物名
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		plant->printName();
		//植物剩余HP
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		plant->printLife();
		//僵尸
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2 + 1);
		if (zombies.size() == 1)
		{
			zombies[0]->printName();
		}
		else
		{
			Print("僵尸×");
			Print((int)zombies.size());
		}
	}

	else if (zombies.size() == 1) 
	{
		//输出僵尸额外信息
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2 - 1);
		zombies[0]->printExtra();
		//输出僵尸名字
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		zombies[0]->printName();
		//输出耐久度百分比 //调试
		/*Cursor(dx + 1, dy + PLOT_HEIGHT / 2 + 1);
		Print("( ");
		Print(zombies[0]->HP * 100 / zombies[0]->maxHP);
		Print("% )");*/
	}
	else if (selected == false && zombies.size() <= PLOT_HEIGHT) 
	{
		for (int i = 0; i < zombies.size(); i++) {
			Cursor(dx + 1, dy + i);
			zombies[i]->printName();
		}
	}
	else if (selected == true && zombies.size() + 2 <= PLOT_HEIGHT) 
	{
		for (int i = 0; i < zombies.size(); i++)
		{
			Cursor(dx + 1, dy + i + 1);
			zombies[i]->printName();
		}
	}
	else 
	{
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		Print("僵尸×");
		Print((int)zombies.size());
	}

	//输出植物信息
	if (plant != nullptr) 
	{
		/*植物名字*/
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		plant->printName();
		
		/*植物剩余HP*/ //调试
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2 + 1);
		plant->printLife();
	}

	if (pumpkin != nullptr)
	{
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2 + 2);
		pumpkin->printName();
	}
	
}

bool Plot::setPlant(Plant* p)
{
	if (plant != nullptr) 
		return false;
	else 
	{
		plant = p;
		refresh = true;
		return true;
	}
}

bool Plot::setPumpKin(Plant* p)
{
	if (pumpkin != nullptr)
		return false;
	else
	{
		pumpkin = p;
		refresh = true;
		return true;
	}
}

void Plot::Plant_eaten(int damage)
{
	if (plant != nullptr) 
	{
		plant->HP -= damage;
		if (plant->HP <= 0) 
			remove_Plant();
		refresh = true;
	}
}

void Plot::PumpKin_eaten(int damage)
{
	if (pumpkin != nullptr)
	{
		pumpkin->HP -= damage;
		if (pumpkin->HP <= 0)
			remove_PumpKin();
		refresh = true;
	}
}

void Plot::eating()
{
	//处理：检测僵尸是否该吃植物
	if (plant != nullptr && zombies.size() != 0) 
	{
		for (auto& var : zombies) 
		{
			var->eating = true;
		}
	}
	else if (pumpkin != nullptr && zombies.size() != 0)
	{
		for (auto& var : zombies)
		{
			var->eating = true;
		}
	}
	else if (plant == nullptr && zombies.size() != 0) 
	{
		for (auto& var : zombies)
		{
			var->eating = false;
		}
	}
}

void Plot::addZombie(Zombie* iZombie)
{
	zombies.push_back(iZombie);
	refresh = true;
}

void Plot::hitZombies(int damage)
{
	for (int i = 0; i < zombies.size(); i++) 
	{
		zombies[i]->hit(damage);
	}
}

void Plot::deleteZombie(Zombie* iZombie)
{
	//删除特定的僵尸
	for (auto itList = zombies.begin(); itList != zombies.end(); )
	{
		if ((*itList) == iZombie)
		{
			itList = zombies.erase(itList);
		}
		else
			itList++;
	}
	refresh = true;
}

bool Map::allPlot(Game& game) //遍历所有地块
{
	for (int i = 0; i < PLOT_NUM_X + 1; i++) 
	{
		for (int j = 0; j < PLOT_NUM_Y; j++) 
		{
			plot[i][j].eating();
			if (plot[i][j].plant != nullptr) 
			{
				plot[i][j].plant->Special(game);
			}
		}
	}

	return true;
}

bool Map::setPlant(int ix, int iy, int type)
{
	Plant* newPlant = nullptr;
	switch (type)
	{
	case PEASHOOTER:
		newPlant = new PeaShooter;
		break;
	case SUNFLOWER: 
		newPlant = new SunFlower;
		break;
	case WALLNUT:
		newPlant = new WallNut;
		break;
	case REPEATER:
		newPlant = new Repeater;
		break;
	case TALL_NUT:
		newPlant = new Tall_nut;
		break;
	case SQUASH:
		newPlant = new Squash;
		break;
	case CHERRY_BOMB:
		newPlant = new CherryBomb;
		break;
	case GARLIC:
		newPlant = new Garlic;
		break;
	case SNOW_PEA:
		newPlant = new SnowPea;
		break;

	default:
		break;
	}
	newPlant->setXY(ix, iy);
	if (!plot[ix][iy].setPlant(newPlant)) 
	{ //种植失败（格子已有植物）
		delete newPlant;
		return false;
	}
	else
		return true;
}

bool Map::setPumpKin(int ix, int iy)
{
	Plant* newPlant = new PumpKin;
	newPlant->setXY(ix, iy);
	if (!plot[ix][iy].setPumpKin(newPlant))
	{ //种植失败（格子已有南瓜头）
		delete newPlant;
		return false;
	}
	else
		return true;
}

void Map::refresh()
{
	for (int i = 0; i < PLOT_NUM_X + 1; i++) 
	{
		for (int j = 0; j < PLOT_NUM_Y; j++) 
		{
			if (plot[i][j].refresh) 
			{
				plot[i][j].paint();
			}
		}
	}
}