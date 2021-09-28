#pragma once
#include"Paint.h"
#include<cstdlib>
#include<string>
using namespace std;

/* �ߴ���Ϣ */
const int PLOT_WIDTH = 11; //��ƺ��ÿ�����ӵĿ�ȣ��ַ�����
const int PLOT_HEIGHT = 5; //��ƺ��ÿ�����ӵĸ߶ȣ��ַ�����
const int PLOT_NUM_X = 9;  //��ƺ�ߴ�Ϊ��PLOT_NUM_X�� 
const int PLOT_NUM_Y = 5;  //          PLOT_NUM_Y��
const int CARD_WIDTH = 11;
const int CARD_HEIGHT = 5;
//�̵�UI����ĸ߶ȣ����ͬ���ڿ�ȣ�
const int STORE_HEIGHT = 7;
//����-��
const int WINDOWS_WIDTH = (PLOT_WIDTH + 1) * PLOT_NUM_X + PLOT_WIDTH * 3 / 2 - 2;
//����-��
//const int WINDOWS_HEIGHT = (PLOT_HEIGHT + 1) * PLOT_NUM_Y + STORE_HEIGHT + 2;
const int WINDOWS_HEIGHT = (PLOT_HEIGHT + 1) * PLOT_NUM_Y + STORE_HEIGHT + 2 + 3;
//�̵괰�ڵ��ϱ߽� - y��ֵ
const int STORE_UP_BOUND = (PLOT_HEIGHT + 1) * PLOT_NUM_Y + 1;
//�̵괰����ֲ��չʾ��Ϣ�Ŀ��
const int PLANT_CARD_WIDTH = 24;
//������ | �÷֡���'|'��λ��
const int RIGHT_LINE_X = WINDOWS_WIDTH - 50;
//������Ϣ������λ��
const int HELP_INFO_Y = WINDOWS_HEIGHT - 1;

/* ȫ���Թ��ܺ������� */
// ����0~n-1�������
inline int RANDOM(int n) { return rand() % n; }

/* һЩȫ�ֳ��� */
//ʱ�����ڣ����룩
const int TIME = 100;
//ֲ��������
const int PLANT_TYPE_MAX = 10;
enum PlantType { SUNFLOWER, PEASHOOTER, WALLNUT, REPEATER, TALL_NUT, SQUASH, CHERRY_BOMB, PUMP_KIN, SNOW_PEA, GARLIC };

//��ʬ������
const int ZOMBIE_TYPE_MAX = 6;
const int ZOMBIE_MAKING = 11;
enum ZombieType { ZOMBIE1, ZOMBIE2, ZOMBIE3, CONEHEAD_ZOMBIE1, CONEHEAD_ZOMBIE2, NEWSPAPER_ZOMBIE1, NEWSPAPER_ZOMBIE2, POLE_ZOMBIE1, POLE_ZOMBIE2, CATAPULT_ZOMBIE, BOX_ZOMBIE };

/*���ֲ�����ı�*/
//ui.h ֲ����������PlantType
//Game.cpp start��shopping�����ּ�ʶ��; Helpֲ������ʾ
//Store.h
//Store.cpp paintCardLine
//Map.cpp setPlant ���case
//���ܣ�Map.h Game.h friend class ...