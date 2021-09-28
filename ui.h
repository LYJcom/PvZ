#pragma once
#include"Paint.h"
#include<cstdlib>
#include<string>
using namespace std;

/* 尺寸信息 */
const int PLOT_WIDTH = 11; //草坪中每个格子的宽度（字符数）
const int PLOT_HEIGHT = 5; //草坪中每个格子的高度（字符数）
const int PLOT_NUM_X = 9;  //草坪尺寸为：PLOT_NUM_X列 
const int PLOT_NUM_Y = 5;  //          PLOT_NUM_Y行
const int CARD_WIDTH = 11;
const int CARD_HEIGHT = 5;
//商店UI界面的高度（宽度同窗口宽度）
const int STORE_HEIGHT = 7;
//窗口-宽
const int WINDOWS_WIDTH = (PLOT_WIDTH + 1) * PLOT_NUM_X + PLOT_WIDTH * 3 / 2 - 2;
//窗口-高
//const int WINDOWS_HEIGHT = (PLOT_HEIGHT + 1) * PLOT_NUM_Y + STORE_HEIGHT + 2;
const int WINDOWS_HEIGHT = (PLOT_HEIGHT + 1) * PLOT_NUM_Y + STORE_HEIGHT + 2 + 3;
//商店窗口的上边界 - y的值
const int STORE_UP_BOUND = (PLOT_HEIGHT + 1) * PLOT_NUM_Y + 1;
//商店窗口中植物展示信息的宽度
const int PLANT_CARD_WIDTH = 24;
//“阳光 | 得分”中'|'的位置
const int RIGHT_LINE_X = WINDOWS_WIDTH - 50;
//帮助信息的所在位置
const int HELP_INFO_Y = WINDOWS_HEIGHT - 1;

/* 全局性功能函数声明 */
// 产生0~n-1的随机数
inline int RANDOM(int n) { return rand() % n; }

/* 一些全局常量 */
//时钟周期（毫秒）
const int TIME = 100;
//植物种类数
const int PLANT_TYPE_MAX = 10;
enum PlantType { SUNFLOWER, PEASHOOTER, WALLNUT, REPEATER, TALL_NUT, SQUASH, CHERRY_BOMB, PUMP_KIN, SNOW_PEA, GARLIC };

//僵尸种类数
const int ZOMBIE_TYPE_MAX = 6;
const int ZOMBIE_MAKING = 11;
enum ZombieType { ZOMBIE1, ZOMBIE2, ZOMBIE3, CONEHEAD_ZOMBIE1, CONEHEAD_ZOMBIE2, NEWSPAPER_ZOMBIE1, NEWSPAPER_ZOMBIE2, POLE_ZOMBIE1, POLE_ZOMBIE2, CATAPULT_ZOMBIE, BOX_ZOMBIE };

/*添加植物后需改变*/
//ui.h 植物种类数，PlantType
//Game.cpp start、shopping中数字键识别; Help植物编号提示
//Store.h
//Store.cpp paintCardLine
//Map.cpp setPlant 添加case
//可能：Map.h Game.h friend class ...