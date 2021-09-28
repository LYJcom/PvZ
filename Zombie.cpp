#include "Zombie.h"
#include "Map.h"
#include "Game.h"

#include<iostream>
using namespace std;

void Zombie::printName()
{
	if (!freezing)
		Print(name);
	else
		Print(name, FREEZING_COLOR);
}

bool Zombie::move(Map& map)
{
	//�䶳Ч����ʱ
	if (freezing) 
	{
		freezing_cnt++;
		if (freezing_cnt >= freezing_time) 
			freezing = false;
	}
	//�ƶ���ʱ
	if (!eating) 
	{
		cnt += (freezing ? 5 : 10);
		if (cnt >= 10 * speed)
		{
			map.plot[x][y].deleteZombie(this);
			x--;
			if (x < 0) //��ʬ����
				return true;
			map.plot[x][y].addZombie(this);
			cnt = 0;
		}
	}
	else 
	{
		//��ֲ�ֹͣ�ƶ���
		if(map.plot[x][y].PumpKin_exist())
			map.plot[x][y].PumpKin_eaten(freezing ? (damage/2) : damage);
		else
			map.plot[x][y].Plant_eaten(freezing ? (damage / 2) : damage);
	}

	//����Ч����ʱ
	if (garlic_effect)
	{
		move_cnt++;
		if (move_cnt >= move_time) 
		{
			ClearGarlic();
			map.plot[x][y].deleteZombie(this);
			if (y == 0) 
				y++;
			else if (y == PLOT_NUM_Y - 1)
				y--;
			else 
				y = RANDOM(2) ? y - 1 : y + 1; //����ƶ���������
			
			map.plot[x][y].addZombie(this);
		}
	}
	return false;
}

void Zombies::addZombie(int x, int y, int type, Game& game)
{
	if (x<0 || x>PLOT_NUM_X || y<0 || y>PLOT_NUM_Y - 1)
		return;
	Zombie* Z = nullptr;
	switch (type)
	{
	case ZOMBIE1:case ZOMBIE2:case ZOMBIE3:
		Z = new Zombie();
		break;
	case CONEHEAD_ZOMBIE1:case CONEHEAD_ZOMBIE2:
		Z = new ConeheadZombie();
		break;
	case NEWSPAPER_ZOMBIE1:case NEWSPAPER_ZOMBIE2:
		Z = new Newspaper_Zombie();
		break;
	case POLE_ZOMBIE1:case POLE_ZOMBIE2:
		Z = new Pole_Zombie();
		break;
	case CATAPULT_ZOMBIE:
		Z = new Catapult_Zombie();
		break;
		return;
	case BOX_ZOMBIE:
		Z = new Box_Zombie();

	default:
		break;
	}
	if (Z != nullptr)
	{
		Z->setXY(x, y);
		game.map.plot[x][y].addZombie(Z);
		zombies.push_back(Z);
	}
}
void Zombies::makeZombie(Game& game)
{
	game.make_cnt++;
	if (game.make_cnt >= game.make_speed)
	{
		int num = game.score / 100;
		if (num > 9)
			num = 9;
		int y, z = ZOMBIE1;
		int make_num = 0;
		if(num > 0)
			make_num = RANDOM(num);
		for(int i = 0; i <= make_num; i++)
		{
			y = RANDOM(PLOT_NUM_Y);
			if(game.score >= 150)
				z = RANDOM(ZOMBIE_MAKING);
			addZombie(PLOT_NUM_X, y, z, game);
		}
		game.make_cnt = 0;
	}
}
bool Zombies::moveZombie(Game& game)
{
	for (auto& var : zombies)
	{
		if (var->getName() != "Ͷʯ����ʬ")
		{
			if (var->move(game.map))
				return true;
		}
		else
		{
			if (var->move(game))
				return true;
		}
	}
	return false;
}
void Zombies::clearZombie(Game& game)
{
	//ɾ��Ѫ��Ϊ��Ľ�ʬ
	for (auto itList = zombies.begin(); itList != zombies.end(); )
	{
		if ((*itList)->HP <= 0)
		{
			//��ɱ�Ʒ�
			game.score += (*itList)->score;

			/*��ӡ�÷�*/
			//Cursor(RIGHT_LINE_X + 4, STORE_UP_BOUND + 1);
			Cursor(RIGHT_LINE_X + 4, 1);
			Print("[������", SUN_AND_SCORE_COLOR);
			Print(game.score, SUN_AND_SCORE_COLOR);
			Print("]", SUN_AND_SCORE_COLOR);

			game.map.plot[(*itList)->x][(*itList)->y].deleteZombie(*itList);
			delete (*itList);
			itList = zombies.erase(itList);
		}
		else
		{
			itList++;
		}
	}
}
bool Zombies::run(Game& game)
{
	makeZombie(game);
	if (moveZombie(game))
	{
		return false;
	}
	clearZombie(game);
	return true;
}


void Newspaper_Zombie::printExtra()
{
	if (HP <= transHP) {
		cout << "(�ޱ�ֽ)";
	}
	else {
		cout << "(�б�ֽ)";
	}
}

void Newspaper_Zombie::hit(int idamage)
{
	HP -= idamage;
	if (HP <= transHP) 
	{
		speed = speed_Plus;
		damage = attack_Plus;
	}
}


void Pole_Zombie::printExtra()
{
	if (hasPole) {
		cout << "(�гŸ�)";
	}
	else {
		cout << "(�޳Ÿ�)";
	}
}

bool Pole_Zombie::move(Map& map)
{
	//�гŸˡ��˴���ֲ�ֲ���Խ������Խ��һ��
	if (hasPole && eating && map.plot[x][y].plant->name != " �߼�� ") 
	{
		map.plot[x][y].deleteZombie(this);
		x--;
		if (x < 0) //��ʬ����
			return true;
		map.plot[x][y].addZombie(this);
		//��������¸��ӣ����״̬
		hasPole = false; eating = false; garlic_effect = false;
		cnt = 0;
		speed = speed2;//�����ٶ�Ϊ����֮����ٶ�
		return false;

	}
	else //���򣬵�����ͨ��ʬ�����ࣩ���н��߼�
	{ 
		return Zombie::move(map);
	}
}

void Catapult_Zombie::printName()
{
	if (HP >= 500)
		Print(name);
	else if (HP >= 250)
		Print(name, GROUND_COLOR);
	else
		Print(name, REMOVE_COLOR);
}
bool Catapult_Zombie::move(Game& game)
{
	if (x <= 6 && First_three_plots)
		First_three_plots = false;
	game.map.plot[x][y].delete_Plants();
	if (First_three_plots || none_basketball)
	{
		cnt += 10;
	}
	if (cnt >= 10 * speed)
	{
		game.map.plot[x][y].deleteZombie(this);
		x--;
		if (x < 0) //��ʬ����
			return true;
		game.map.plot[x][y].addZombie(this);
		cnt = 0;
	}
	if (!First_three_plots && !none_basketball)
	{
		if (num > 0)
		{
			bool Attack = false;
			for (int i = x; i >= 0; i--)
			{
				if (game.map.plot[i][y].plant != nullptr || game.map.plot[i][y].PumpKin_exist())
				{
					Attack = true;
					break;
				}
			}
			if (Attack)
			{
				cnt_shoot++;
				if (cnt_shoot >= speed_shoot)
				{
					cnt_shoot = 0;
					Bullet* b = new BasketBall();
					b->setXY(x, y);
					game.bullets.push_back(b);
					num--;
				}
			}
			else
			{
				cnt += 10;
			}
		}
		else
			none_basketball = true;
	}
	return false;
}

void Box_Zombie::printName()
{
	if (!freezing)
		Print(name, REMOVE_COLOR);
	else
		Print(name, FREEZING_COLOR);
}
bool Box_Zombie::move(Map& map)
{
	if (!bomb_flag) 
	{
		bomb_counter++;
		if (bomb_counter >= bomb_time) 
		{
			int coin = RANDOM(3);
			if (coin) 
			{
				bomb_flag = true; 
				cnt = 0;
			}
			else
			{ 
				bomb_counter = 0;
			}
		}
		//�䶳Ч����ʱ
		if (freezing)
		{
			freezing_cnt++;
			if (freezing_cnt >= freezing_time)
				freezing = false;
		}
		//�ƶ���ʱ
		if (!eating)
		{
			cnt += (freezing ? 5 : 10);
			if (cnt >= 10 * speed)
			{
				map.plot[x][y].deleteZombie(this);
				x--;
				if (x < 0) //��ʬ����
					return true;
				map.plot[x][y].addZombie(this);
				cnt = 0;
			}
		}
		else
		{
			//��ֲ�ֹͣ�ƶ���
			if (map.plot[x][y].PumpKin_exist())
				map.plot[x][y].PumpKin_eaten(freezing ? (damage / 2) : damage);
			else
				map.plot[x][y].Plant_eaten(freezing ? (damage / 2) : damage);
		}

		//����Ч����ʱ
		if (garlic_effect)
		{
			move_cnt++;
			if (move_cnt >= move_time)
			{
				ClearGarlic();
				map.plot[x][y].deleteZombie(this);
				if (y == 0)
					y++;
				else if (y == PLOT_NUM_Y - 1)
					y--;
				else
					y = RANDOM(2) ? y - 1 : y + 1; //����ƶ���������

				map.plot[x][y].addZombie(this);
			}
		}
	}
	else 
	{
		HP = -1; 
		
		map.plot[x - 1][y - 1].delete_Plants();
		map.plot[x - 1][y].delete_Plants();
		map.plot[x - 1][y + 1].delete_Plants();
		map.plot[x][y - 1].delete_Plants();
		map.plot[x][y].delete_Plants();
		map.plot[x][y + 1].delete_Plants();
		map.plot[x + 1][y - 1].delete_Plants();
		map.plot[x + 1][y].delete_Plants();
		map.plot[x + 1][y + 1].delete_Plants();
	}
	return false;
}