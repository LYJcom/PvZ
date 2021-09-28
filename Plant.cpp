#include "Plant.h"
#include "Game.h"
#include<iostream>
using namespace std;

void PeaShooter::Special(Game& game)
{
	/*先判断右侧是否存在僵尸，不存在则不攻击*/
	bool Attack = false;
	for (int i = x; i <= PLOT_NUM_X; i++) 
	{
		if (game.map.plot[i][y].zombies.size() != 0) 
		{
			Attack = true;
			break;
		}
	}
	if (Attack)
	{
		cnt++;
		if (cnt >= speed) 
		{
			cnt = 0;
			Bullet *b = new Bullet;
			b->setXY(x, y);
			game.bullets.push_back(b);
		}
	}
}
void SunFlower::Special(Game& game)
{
	cnt++;
	if (cnt >= speed) 
	{
		cnt = 0;
		game.store.addSun();
		speed = 240 * 1000 / 10 / (TIME); //24秒产生一次阳光
	}
}

void Repeater::Special(Game& game)
{
	/*先判断右侧是否存在僵尸，不存在则不攻击*/
	bool Attack = false;
	for (int i = x; i <= PLOT_NUM_X; i++)
	{
		if (game.map.plot[i][y].zombies.size() != 0)
		{
			Attack = true;
			break;
		}
	}
	if (Attack)
	{
		cnt++;
		if (cnt >= speed)
		{
			cnt = 0;
			Bullet *b = new Bullet;
			b->setXY(x, y);
			game.bullets.push_back(b);
		}
	}
}

void Plant::printName()
{
	Print(name, nameColor);
}

void Plant::printLife() //调试
{
	//输出HP
	//cout << "<HP-" << HP * 100 / maxHP << "%>";
}

void WallNut::printName()
{
	if (HP >= 2666)
		Print(name, nameColor);
	else if (HP >= 1333)
		Print("坚 果", nameColor);
	else
		Print("坚", nameColor);
}

void Tall_nut::printName()
{
	if (HP >= 5333)
		Print(name, nameColor);
	else if (HP >= 2666)
		Print(" 高坚 ", nameColor);
	else
		Print(" 高 ", nameColor);
}

void PumpKin::printName()
{
	if (HP >= 2666)
		Print(name, nameColor);
	else if (HP >= 1333)
		Print("南 瓜", nameColor);
	else
		Print("南", nameColor);
}

void Squash::Special(Game& game)
{
	if(counter >= speed)
	{
		if (game.map.plot[x][y].zombies.size() != 0) 
		{
			game.map.plot[x][y].hitZombies(damage);
			game.remove_Plant(x, y);
		}
		else if (x + 1 <= PLOT_NUM_X && game.map.plot[x + 1][y].zombies.size() != 0) 
		{
			game.map.plot[x + 1][y].hitZombies(damage);
			game.remove_Plant(x, y);
		}
		else if (x - 1 >= 0 && game.map.plot[x - 1][y].zombies.size() != 0)
		{
			game.map.plot[x - 1][y].hitZombies(damage);
			game.remove_Plant(x, y);
		}
	}
	if (!flag)
	{
		if (game.map.plot[x][y].zombies.size() != 0)
			flag = true;
		else if (x + 1 <= PLOT_NUM_X && game.map.plot[x + 1][y].zombies.size() != 0)
			flag = true;
		else if (x - 1 >= 0 && game.map.plot[x - 1][y].zombies.size() != 0)
			flag = true;
	}
	else
		counter++;
}

void CherryBomb::Special(Game& game)
{
	if (counter < speed)
		counter++;
	else 
	{
		//中间一列的三个格子
		game.map.plot[x][y].hitZombies(damage);
		if (x - 1 >= 0) game.map.plot[x - 1][y].hitZombies(damage);
		if (x + 1 <= PLOT_NUM_X) game.map.plot[x + 1][y].hitZombies(damage);

		//上侧一列的三个格子
		if (y - 1 >= 0)
		{
			game.map.plot[x][y - 1].hitZombies(damage);
			if (x - 1 >= 0) game.map.plot[x - 1][y - 1].hitZombies(damage);
			if (x + 1 <= PLOT_NUM_X) game.map.plot[x + 1][y - 1].hitZombies(damage);
		}
	
		//下侧一列的三个格子
		if (y + 1 <= PLOT_NUM_Y - 1) 
		{
			game.map.plot[x][y + 1].hitZombies(damage);
			if (x - 1 >= 0) game.map.plot[x - 1][y + 1].hitZombies(damage);
			if (x + 1 <= PLOT_NUM_X) game.map.plot[x + 1][y + 1].hitZombies(damage);
		}

		game.remove_Plant(x, y);
	}
}

void Garlic::printName()
{
	if (HP >= 266)
		Print(name, nameColor);
	else if (HP >= 133)
		Print("大蒜", nameColor);
	else
		Print(" 蒜 ", nameColor);
}
void Garlic::Special(Game& game)
{
	for (auto& var : game.map.plot[x][y].zombies)
	{
		var->SetGarlic();
	}
}

void SnowPea::Special(Game& game)
{
	/*先判断右侧是否存在僵尸，不存在则不攻击*/
	bool Attacking = false;
	for (int i = x; i <= PLOT_NUM_X; i++)
	{
		if (game.map.plot[i][y].zombies.size() != 0)
		{
			Attacking = true; 
			break;
		}
	}
	if (Attacking) 
	{
		cnt++;
		if (cnt >= speed) 
		{
			cnt = 0;
			Bullet* p = new SnowBullet;
			p->setXY(x, y);
			game.bullets.push_back(p);
		}
	}
}
