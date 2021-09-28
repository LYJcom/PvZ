#pragma once
#include"ui.h"
#include<string>
#include<list>
using namespace std;

class Map;
class Game;

//��ͨ��ʬ
class Zombie
{
protected:
	int x, y; //���ڵؿ�����

	int HP; //��ǰѪ��
	int maxHP; //���Ѫ����270��

	string name; //��ʬ��

	int speed; //�ƶ��ٶȣ��ƶ�һ������ʱ�䣩

	int cnt; //�����ƶ��ļ���

	int damage; //����������λʱ������˺���

	int score; //��ɱ�÷֣�50��

	bool eating; //��Ǵ��ڳ�ֲ���״̬

	bool freezing; //����Ч��
	int freezing_time; //����Ч������ʱ��
	int freezing_cnt;

	bool garlic_effect; //�Ƿ�ճ��˴���
	int move_cnt;
	int move_time;

protected:
	//���Բ����趨
	void Setting(const string n, int s = 50, int hp = 250, int ten_speed = 75, int d = 100)
	{
		name = n;
		score = s;
		maxHP = HP = hp;
		speed = ten_speed; //�ٶȣ���ten_speed/10�����ƶ�һ��
		damage = d / 10; //��������d���˺�/��
	}

	//�����ʬ����
	virtual void printName();
	//��ʬ������Ϣ
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
		Setting("  ��ʬ  ");
	}
	
	const string& getName() const //���ؽ�ʬ����
	{ 
		return name;
	}

	void setXY(int ix, int iy) //�趨��ʼλ�� 
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
	
	virtual bool move(Map& map); //��ʬ�ж�������λ�ơ���ֲ��ȶ�����������ֵ�����Ƿ���
	virtual bool move(Game& game) { return false; };

	virtual void hit(int damage) //������
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
		Setting("·�Ͻ�ʬ", 75, 700);
	}
};

class Newspaper_Zombie :public Zombie 
{
	//�ٽ��
	int transHP;
	//��ֽû�˺���ٶ� 1.2��/��
	int speed_Plus = 12 * 1000 / 10 / TIME;
	//��ֽû�˺�Ĺ�����
	int attack_Plus = 200;
public:
	Newspaper_Zombie() 
	{
		Setting("������ʬ", 125, 300); 
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
	//��д��Ѫ��������ֽû��Ҫ���٣�
	void hit(int idamage);
	
};

class Pole_Zombie :public Zombie 
{
	//�ٽ�㣺�Ƿ��гŸ�
	bool hasPole;
	//����֮����ٶ� 4.5��/��
	int speed2 = 45 * 1000 / 10 / TIME;
public:
	Pole_Zombie() 
	{
		Setting("�Ÿ˽�ʬ", 100, 430, 20); 
		hasPole = true; 
	}
	void printExtra();
	bool move(Map& map);
};

class Catapult_Zombie :public Zombie
{
	int num; //������
	int cnt_shoot, speed_shoot;
	bool First_three_plots;
	bool none_basketball;
public:
	Catapult_Zombie() 
	{
		Setting("Ͷʯ����ʬ", 500, 850, 25); 
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
	//һ��ʱ��󴥷������Ա�
	int bomb_time;
	//�Ա�ʱ�����
	int bomb_counter;
	//�Ƿ�������ը
	bool bomb_flag;
public:
	Box_Zombie()
	{
		Setting("С��ʬ", 250, 800, 22);
		bomb_time = 30;
		bomb_counter = 0;
		bomb_flag = false;
	}
	void printName();
	bool move(Map& map);
};
