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

	list<Bullet*> bullets; //�ӵ�����

	int state; //״̬������������״̬������ֲ���Ϸ��ͣ
	enum GAME_STATE { PROCEED, STORE, REMOVE, PAUSE };

	void remove(); //����ֲ��

	void shopping(); //����ֲ��
	int planting_type; //��ǰ׼����ֲ��ֲ������

	int make_speed; //��ʬ�����ٶ�
	int make_cnt;

	int score; //�÷�
	int x, y; //��ǰ����λ��

	void Unselected(); //�ر�ѡ��

	void remove_Plant(int ix, int iy); //����ĳ��λ�õ�ֲ��
	void remove_Plants(int ix, int iy); //����ĳ��λ�õ�����ֲ��

	void moveBullet(); //�ӵ��ƶ�

	void ifBulletHit(); //�ӵ����н�ʬ�ı߽�����ж�

	void printBullet(); //��ʾ�ӵ�

	void Pause_Display(); // ��ͣ����ʾ
	void Pause_Hide(); //��ͣ������
	
	void Help();//������Ϣ�����
	bool Help_refresh; //�л�״̬��ʾ

	void pause(); //��ͣ
	
	void gameover(); //��Ϸ����

	void gameExit(); //�����˳���Ϸ

public:
	void init();//��Ϸ��ʼ��
	
	void start();//��Ϸ����

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

