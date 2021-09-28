#include "Map.h"
#include<iostream>
using namespace std;

void Map::init()
{
	system("cls");
	//�����ߣ��ݵؿ�ı߽磩�Ļ���
	paintPlotLine();
	//ÿ�����ӳ�ʼ��
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

	//�����ߣ��ݵؿ�ı߽磩�Ļ���
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

	//�������������
	string str(PLOT_WIDTH, ' ');
	for (int i = 0; i < PLOT_HEIGHT; i++) 
	{
		Cursor(dx, dy + i);
		Print(str);
	}

	
	if (selected) //ѡ��״̬ ���ѡ���
	{
		string str(PLOT_WIDTH - 2, '-'); //������Ƕ���ӵĺ���
		Cursor(dx, dy);
		//Print("+" + str + "+");
		cout << "+" << str << "+";
		for (int i = 1; i < PLOT_HEIGHT - 1; i++) //��ӡ������Ƕ���ӵ�����
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

	if(remove_selected) //����ѡ��״̬ ���ѡ���
	{
		string str(PLOT_WIDTH - 2, '-'); //������Ƕ���ӵĺ���
		Cursor(dx, dy);
		Print("x" + str + "x", REMOVE_COLOR);
		for (int i = 1; i < PLOT_HEIGHT - 1; i++) //��ӡ������Ƕ���ӵ�����
		{
			Cursor(dx, dy + i);
			Print("|", REMOVE_COLOR);
			Cursor(dx + PLOT_WIDTH - 1, dy + i);
			Print("|", REMOVE_COLOR);
		}
		Cursor(dx, dy + PLOT_HEIGHT - 1);
		Print("x" + str + "x", REMOVE_COLOR);
	}

	//���ֲ���ʬ����Ϣ
	if (plant != nullptr && zombies.size() == 0) 
	{
		//ֲ����
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		plant->printName();
		//ֲ��ʣ��HP
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2 + 1);
		plant->printLife();
	}
	else if (plant != nullptr && zombies.size() != 0) 
	{
		//ֲ����
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		plant->printName();
		//ֲ��ʣ��HP
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		plant->printLife();
		//��ʬ
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2 + 1);
		if (zombies.size() == 1)
		{
			zombies[0]->printName();
		}
		else
		{
			Print("��ʬ��");
			Print((int)zombies.size());
		}
	}

	else if (zombies.size() == 1) 
	{
		//�����ʬ������Ϣ
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2 - 1);
		zombies[0]->printExtra();
		//�����ʬ����
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		zombies[0]->printName();
		//����;öȰٷֱ� //����
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
		Print("��ʬ��");
		Print((int)zombies.size());
	}

	//���ֲ����Ϣ
	if (plant != nullptr) 
	{
		/*ֲ������*/
		Cursor(dx + 1, dy + PLOT_HEIGHT / 2);
		plant->printName();
		
		/*ֲ��ʣ��HP*/ //����
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
	//������⽩ʬ�Ƿ�ó�ֲ��
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
	//ɾ���ض��Ľ�ʬ
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

bool Map::allPlot(Game& game) //�������еؿ�
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
	{ //��ֲʧ�ܣ���������ֲ�
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
	{ //��ֲʧ�ܣ����������Ϲ�ͷ��
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