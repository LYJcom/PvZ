#include "Bullet.h"
#include "Map.h"
#include "ui.h"
using namespace std;

Bullet::Bullet()
{
	speed = 1; //0.1��һ�θ���
	damage = 20; //�����ӵ��˺�
	cnt = 0;
	hit = false;
}

void Bullet::setXY(int dx, int dy)
{
	x = (dx + 1) * (PLOT_WIDTH + 1) - 4;
	//y = dy * (PLOT_HEIGHT + 1) + 1 + PLOT_HEIGHT / 2;
	y = dy * (PLOT_HEIGHT + 1) + 1 + PLOT_HEIGHT / 2 + 10;
}

void Bullet::move(Map& map)
{
	cnt++;
	int dx = x / (PLOT_WIDTH + 1);
	//int dy = (y - 1 - PLOT_HEIGHT / 2) / (PLOT_HEIGHT + 1);
	int dy = (y - 1 - 10 - PLOT_HEIGHT / 2) / (PLOT_HEIGHT + 1);

	//�ж��Ƿ����
	if (map.plot[dx][dy].zombies.size() > 0 && !hit) 
	{
		hitZombie(map.plot[dx][dy].zombies[0]);
		map.plot[dx][dy].setRefresh();
		if (x % (PLOT_WIDTH + 1) == 0)  //�ڵ����ǻ��Ʊ߽紦���޲��߽���"#"
		{
			Cursor(x, y);
			Print("#", GRASS_COLOR);
		}
		hit = true;
		return;
	}
	if (cnt == speed) 
	{
		//���޲������ӵ�֮ǰλ�ô����ӵ�ͼ��
		map.plot[dx][dy].setRefresh();
		if (x % (PLOT_WIDTH + 1) == 0)  //�ڵ����ǻ��Ʊ߽紦���޲��߽���"#"
		{
			Cursor(x, y);
			Print("#", GRASS_COLOR);
		}
		x += 4;
		dx = x / (PLOT_WIDTH + 1);
		
		//�ӵ������߽�
		if (dx > PLOT_NUM_X)
		{
			hit = true;
			return;
		}
		
		cnt = 0;
	}
}

void Bullet::ifHit(Map& map)
{
	int dx = x / (PLOT_WIDTH + 1);
	//int dy = (y - 1 - PLOT_HEIGHT / 2) / (PLOT_HEIGHT + 1);
	int dy = (y - 1 - 10 - PLOT_HEIGHT / 2) / (PLOT_HEIGHT + 1);

	//�ж��Ƿ����
	if (map.plot[dx][dy].zombies.size() > 0 && !hit)
	{
		hitZombie(map.plot[dx][dy].zombies[0]);
		map.plot[dx][dy].setRefresh();
		if (x % (PLOT_WIDTH + 1) == 0)  //�ڵ����ǻ��Ʊ߽紦���޲��߽���"#"
		{
			Cursor(x, y);
			Print("#", GRASS_COLOR);

		}
		hit = true;
		return;
	}
}

void Bullet::paint()
{
	Cursor(x, y);
	Print("��", FOREGROUND_GREEN);
}

void Bullet::hitZombie(Zombie* z)
{
	z->hit(damage);
}

void SnowBullet::hitZombie(Zombie* z)
{
	z->hit(damage);
	z->setFreezing();
}

void SnowBullet::paint()
{
	Cursor(x, y);
	Print("��", SNOW_COLOR);
}


void BasketBall::move(Map& map)
{
	cnt++;
	int dx = x / (PLOT_WIDTH + 1);
	int dy = (y - 1 - 10 - PLOT_HEIGHT / 2) / (PLOT_HEIGHT + 1);

	//�ж��Ƿ����
	if (map.plot[dx][dy].PumpKin_exist() && !hit)
	{
		map.plot[dx][dy].PumpKin_eaten(damage);
		map.plot[dx][dy].setRefresh();
		if (x % (PLOT_WIDTH + 1) == 0)  //�ڵ����ǻ��Ʊ߽紦���޲��߽���"#"
		{
			Cursor(x, y-1);
			Print("#", GRASS_COLOR);
		}
		hit = true;
		return;
	}
	else if (map.plot[dx][dy].plant != nullptr && !hit)
	{
		map.plot[dx][dy].Plant_eaten(damage);
		map.plot[dx][dy].setRefresh();
		if (x % (PLOT_WIDTH + 1) == 0)  //�ڵ����ǻ��Ʊ߽紦���޲��߽���"#"
		{
			Cursor(x, y-1);
			Print("#", GRASS_COLOR);
		}
		hit = true;
		return;
	}
	if (cnt == speed)
	{
		//���޲������ӵ�֮ǰλ�ô����ӵ�ͼ��
		map.plot[dx][dy].setRefresh();
		if (x % (PLOT_WIDTH + 1) == 0)  //�ڵ����ǻ��Ʊ߽紦���޲��߽���"#"
		{
			Cursor(x, y-1);
			Print("#", GRASS_COLOR);
		}
		x -= 4;
		dx = x / (PLOT_WIDTH + 1);

		//�ӵ������߽�
		if (dx < 0)
		{
			hit = true;
			return;
		}

		cnt = 0;
	}
}
void BasketBall::paint()
{
	Cursor(x, y - 1);
	Print("��", SUN_AND_SCORE_COLOR);
}