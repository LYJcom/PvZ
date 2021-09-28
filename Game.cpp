#include "Game.h"
#include<iostream>
#include<ctime>
#include<conio.h>
using namespace std;

void Game::init() //Game初始化
{
	map.init();
	store.init();

	state = PROCEED;
	Help_refresh = true;
	x = y = 0;
	planting_type = 0; //当前准备种植的植物类型

	score = 0;

	//5秒产生一次僵尸 //18
	make_speed = 50 * 1000 / 10 / TIME;
	make_cnt = 0;

	score = 0;
	//输出得分
	//Cursor(RIGHT_LINE_X + 4, STORE_UP_BOUND + 1);
	Cursor(RIGHT_LINE_X + 4, 1);
	Print("[分数：", SUN_AND_SCORE_COLOR);
	Print(score, SUN_AND_SCORE_COLOR);
	Print("]", SUN_AND_SCORE_COLOR);
}

void Game::start()
{
	while (1)
	{

		if (state == PROCEED) //游戏进程正常
		{
			/* 键盘按键识别 */
			char c;
			if (_kbhit()) //如果当前有键盘键入
			{
				c = _getch();
				switch (c)
				{
				case ' ': //空格键暂停
					pause();
					break;
					
				case 'x':case 'X': //按x/X进入铲除植物
					state = REMOVE;
					Help_refresh = true;
					map.plot[x][y].setSelected(0);
					break;
				case '*'://完成所有冷却（便于测试）
					store.renew();
					break;

				default: //数字键入
					if (c >= '0' && c <= '9')
					{
						planting_type = (c - '0') - 1;
						if (planting_type == -1)
							planting_type = 9;
						state = STORE;
						Help_refresh = true;
						map.plot[x][y].setSelected(1);
						/* 开启商店选择 */
						store.plants[planting_type].setSelect();
						break;
					}
				}
			}
			/*按键识别结束*/
		}
		else if (state == STORE) //当前状态为购买植物
		{
			shopping();
		}
		else if (state == REMOVE) //当前状态为铲除植物
		{
			remove();
		}

		//遍历：植物
		if (!map.allPlot(*this))
		{
			break;
		}

		moveBullet(); //子弹移动

		if (!zombies.run(*this))
		{
			gameover();
			break;
		}

		ifBulletHit(); //子弹边界情况

		store.run(); //商店运行


		/*刷新显示*/
		map.refresh();//草地的每个格子

		printBullet(); //打印子弹

		//帮助信息的输出显示
		Help();

		Sleep(TIME);
	}

}

void Game::remove()
{
	//键盘按键识别
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
		case -32:
			map.plot[x][y].setUnSelected();
			ch = _getch();
			switch (ch)
			{
			case 72://上
				if (y > 0)
					y--;
				break;
			case 80://下
				if (y < PLOT_NUM_Y - 1)
					y++;
				break;
			case 75://左
				if (x > 0)
					x--;
				break;
			case 77://右
				if (x < PLOT_NUM_X - 1)
					x++;
				break;
			default:
				break;
			}
			map.plot[x][y].setSelected(0);
			break;
		case '\r':
			remove_Plant(x, y);
			//这里不用break，接下来，关闭焦点退出
		case 27://ESC
			Unselected();
			break;
			//空格键暂停
		case ' ':
			pause();
			break;
		case '*'://完成所有冷却（便于测试）
			store.renew();
			break;

		default:break;
		}
	}
	//按键识别结束
}
void Game::remove_Plant(int ix, int iy)
{
	if (ix<0 || ix>PLOT_NUM_X || iy<0 || iy>PLOT_NUM_Y - 1)
		return;
	map.plot[ix][iy].remove_Plant();
}
void Game::remove_Plants(int ix, int iy)
{
	if (ix<0 || ix>PLOT_NUM_X || iy<0 || iy>PLOT_NUM_Y - 1)
		return;
	map.plot[ix][iy].delete_Plants();
}

void Game::shopping()
{
	//键盘按键识别
	char c;
	if (_kbhit())
	{
		c = _getch();
		switch (c)
		{
		case -32: //判断是否键入了方向键
			map.plot[x][y].setUnSelected();
			c = _getch();
			switch (c)
			{
			case 72://上
				if (y > 0)
					y--;
				break;
			case 80://下
				if (y < PLOT_NUM_Y - 1)
					y++;
				break;
			case 75://左
				if (x > 0)
					x--;
				break;
			case 77://右
				if (x < PLOT_NUM_X - 1)
					x++;
				break;
			default:
				break;
			}
			map.plot[x][y].setSelected(1);
			break;
		case 27: //ESC键
			store.plants[planting_type].setUnSelect();
			Unselected();
			break;
		case '\r': //回车键
			if (store.pay(planting_type, x, y, map)) //如果购买成功
			{
				store.plants[planting_type].setUnSelect();
				Unselected();
			}
			break;
		case ' ': //空格键暂停
			pause();
			break;
		case '*'://完成所有冷却（便于测试）
			store.renew();
			break;

			/*购买植物的按键识别*/
		default:
			if (c >= '0' && c <= '9')
			{
				int key = c - '0' - 1;
				if (key >= 0 && key < PLANT_TYPE_MAX)
				{
					store.plants[planting_type].setUnSelect();
					planting_type = key;
					store.plants[planting_type].setSelect();
				}
				else if (key == -1)
				{
					store.plants[planting_type].setUnSelect();
					planting_type = 9;
					store.plants[planting_type].setSelect();
				}
			}
			break;
		}
	}
	//按键识别结束
}

void Game::pause()
{
	int temp = state;
	state = PAUSE;
	Help_refresh = true;
	Help();
	while (true)
	{
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case ' '://空格结束暂停
				state = temp;
				Help_refresh = true;
				Help();
				Pause_Hide();
				return;
				break;

			case 27: //ESC键
				gameExit();
				break;

			default:;
			}
		}
		Sleep(TIME);
	}

}
void Game::Pause_Display()
{
	string str1(13, '#');
	Cursor(4 * (PLOT_WIDTH + 1), 16);
	Print(str1);
	Cursor(4 * (PLOT_WIDTH + 1), 22);
	Print(str1);

	string str2 = "#           #";
	for (int i = 0; i < 5; i++)
	{
		Cursor(4 * (PLOT_WIDTH + 1), 17 + i);
		Print(str2);
	}
	Cursor(4 * (PLOT_WIDTH + 1) + 2, 19);
	Print(" 游戏暂停");
	Cursor(4 * (PLOT_WIDTH + 1) + 1, 20);
	Print(" 退出：Esc");
}
void Game::Pause_Hide()
{
	string str(13, '#');
	Cursor(4 * (PLOT_WIDTH + 1), 16);
	Print(str, GRASS_COLOR);
	Cursor(4 * (PLOT_WIDTH + 1), 22);
	Print(str, GRASS_COLOR);
	for (int i = 0; i < 5; i++)
	{
		Cursor(4 * (PLOT_WIDTH + 1), 17 + i);
		Print("#", GRASS_COLOR);
		Cursor(5 * (PLOT_WIDTH + 1), 17 + i);
		Print("#", GRASS_COLOR);
	}
	map.plot[4][1].paint();
}

void Game::Unselected()
{
	state = PROCEED; 
	Help_refresh = true;
	map.plot[x][y].setUnSelected();
}

void Game::Help()
{
	if (Help_refresh) 
	{
		//清空
		string str(WINDOWS_WIDTH, ' ');
		Cursor(0, HELP_INFO_Y);
		cout << str;
		Cursor(0, HELP_INFO_Y);
		if (state == PROCEED) 
		{
			Print(" <操作提示> ");
			Print(" 植物编号选择：\"1/2/3/4/5/6/7/8/9/0\"数字键 | 铲子：\"x\"键");
			Cursor(WINDOWS_WIDTH - 18, 0);
			Print("|暂停游戏：空格键|", PAUSE_COLOR);
		}
		else if (state == STORE) 
		{
			Print(" <操作提示> ");
			Print(" 植物编号选择：\"1/2/3/4/5/6/7/8/9/0\"数字键 | 确认种植：回车键 | 返回：Esc键");
			Cursor(WINDOWS_WIDTH - 18, 0);
			Print("|暂停游戏：空格键|", PAUSE_COLOR);
		}
		else if (state == REMOVE) 
		{
			Print(" <操作提示> ");
			Print(" 确认铲除：回车键 | 返回：Esc键");
			Cursor(WINDOWS_WIDTH - 18, 0);
			Print("|暂停游戏：空格键|", PAUSE_COLOR);
		}
		else if (state == PAUSE) 
		{
			Print(" <暂停中> ");
			Cursor(WINDOWS_WIDTH - 18, 0);
			Print("|继续游戏：空格键|", PAUSE_COLOR);
			Pause_Display();
		}
		Help_refresh = false;
	}
}



void Game::gameover()
{
	system("cls");
	Cursor(WINDOWS_WIDTH / 2 - 8, WINDOWS_HEIGHT / 2 - 1);
	Print("僵", FOREGROUND_GREEN);
	Sleep(500);
	Print("尸", FOREGROUND_GREEN);
	Sleep(500);
	Print("吃");
	Sleep(500);
	Print("了");
	Sleep(500);
	Print("你");
	Sleep(500);
	Print("的");
	Sleep(500);
	Print("脑");
	Sleep(500);
	Print("子");
	Sleep(500);
	Print("!");
	Sleep(500);
	Cursor(WINDOWS_WIDTH / 2 - 6, WINDOWS_HEIGHT / 2 + 1);
	cout << "SCORE：" << score << '!';
	Cursor(0, WINDOWS_HEIGHT - 2);
	system("pause");
	exit(0);
}

void Game::gameExit()
{
	system("cls");
	Cursor(WINDOWS_WIDTH / 2 - 6, WINDOWS_HEIGHT / 2 - 1);
	Print("GAME OVER");
	Cursor(WINDOWS_WIDTH / 2 - 6, WINDOWS_HEIGHT / 2 + 1);
	cout << "SCORE：" << score << '!';
	Cursor(0, WINDOWS_HEIGHT - 2);
	system("pause");
	exit(0);
}


void Game::moveBullet()
{
	list<Bullet*> ::iterator it;
	//全部遍历，执行移动
	for (it = bullets.begin(); it != bullets.end(); it++)
	{
		(*it)->move(map);
	}
	for (it = bullets.begin(); it != bullets.end(); )
	{
		if ((*it)->hit)
		{
			delete (*it);
			it = bullets.erase(it);
		}
		else
			it++;
	}
}

void Game::ifBulletHit()
{
	list<Bullet*> ::iterator it;
	for (it = bullets.begin(); it != bullets.end(); it++)
	{
		(*it)->ifHit(map);
	}
}

void Game::printBullet()
{
	list<Bullet*> ::iterator it;
	//全部遍历，执行输出
	for (it = bullets.begin(); it != bullets.end(); it++)
	{
		(*it)->paint();
	}
}