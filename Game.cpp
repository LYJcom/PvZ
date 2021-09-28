#include "Game.h"
#include<iostream>
#include<ctime>
#include<conio.h>
using namespace std;

void Game::init() //Game��ʼ��
{
	map.init();
	store.init();

	state = PROCEED;
	Help_refresh = true;
	x = y = 0;
	planting_type = 0; //��ǰ׼����ֲ��ֲ������

	score = 0;

	//5�����һ�ν�ʬ //18
	make_speed = 50 * 1000 / 10 / TIME;
	make_cnt = 0;

	score = 0;
	//����÷�
	//Cursor(RIGHT_LINE_X + 4, STORE_UP_BOUND + 1);
	Cursor(RIGHT_LINE_X + 4, 1);
	Print("[������", SUN_AND_SCORE_COLOR);
	Print(score, SUN_AND_SCORE_COLOR);
	Print("]", SUN_AND_SCORE_COLOR);
}

void Game::start()
{
	while (1)
	{

		if (state == PROCEED) //��Ϸ��������
		{
			/* ���̰���ʶ�� */
			char c;
			if (_kbhit()) //�����ǰ�м��̼���
			{
				c = _getch();
				switch (c)
				{
				case ' ': //�ո����ͣ
					pause();
					break;
					
				case 'x':case 'X': //��x/X�������ֲ��
					state = REMOVE;
					Help_refresh = true;
					map.plot[x][y].setSelected(0);
					break;
				case '*'://���������ȴ�����ڲ��ԣ�
					store.renew();
					break;

				default: //���ּ���
					if (c >= '0' && c <= '9')
					{
						planting_type = (c - '0') - 1;
						if (planting_type == -1)
							planting_type = 9;
						state = STORE;
						Help_refresh = true;
						map.plot[x][y].setSelected(1);
						/* �����̵�ѡ�� */
						store.plants[planting_type].setSelect();
						break;
					}
				}
			}
			/*����ʶ�����*/
		}
		else if (state == STORE) //��ǰ״̬Ϊ����ֲ��
		{
			shopping();
		}
		else if (state == REMOVE) //��ǰ״̬Ϊ����ֲ��
		{
			remove();
		}

		//������ֲ��
		if (!map.allPlot(*this))
		{
			break;
		}

		moveBullet(); //�ӵ��ƶ�

		if (!zombies.run(*this))
		{
			gameover();
			break;
		}

		ifBulletHit(); //�ӵ��߽����

		store.run(); //�̵�����


		/*ˢ����ʾ*/
		map.refresh();//�ݵص�ÿ������

		printBullet(); //��ӡ�ӵ�

		//������Ϣ�������ʾ
		Help();

		Sleep(TIME);
	}

}

void Game::remove()
{
	//���̰���ʶ��
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
			case 72://��
				if (y > 0)
					y--;
				break;
			case 80://��
				if (y < PLOT_NUM_Y - 1)
					y++;
				break;
			case 75://��
				if (x > 0)
					x--;
				break;
			case 77://��
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
			//���ﲻ��break�����������رս����˳�
		case 27://ESC
			Unselected();
			break;
			//�ո����ͣ
		case ' ':
			pause();
			break;
		case '*'://���������ȴ�����ڲ��ԣ�
			store.renew();
			break;

		default:break;
		}
	}
	//����ʶ�����
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
	//���̰���ʶ��
	char c;
	if (_kbhit())
	{
		c = _getch();
		switch (c)
		{
		case -32: //�ж��Ƿ�����˷����
			map.plot[x][y].setUnSelected();
			c = _getch();
			switch (c)
			{
			case 72://��
				if (y > 0)
					y--;
				break;
			case 80://��
				if (y < PLOT_NUM_Y - 1)
					y++;
				break;
			case 75://��
				if (x > 0)
					x--;
				break;
			case 77://��
				if (x < PLOT_NUM_X - 1)
					x++;
				break;
			default:
				break;
			}
			map.plot[x][y].setSelected(1);
			break;
		case 27: //ESC��
			store.plants[planting_type].setUnSelect();
			Unselected();
			break;
		case '\r': //�س���
			if (store.pay(planting_type, x, y, map)) //�������ɹ�
			{
				store.plants[planting_type].setUnSelect();
				Unselected();
			}
			break;
		case ' ': //�ո����ͣ
			pause();
			break;
		case '*'://���������ȴ�����ڲ��ԣ�
			store.renew();
			break;

			/*����ֲ��İ���ʶ��*/
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
	//����ʶ�����
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
			case ' '://�ո������ͣ
				state = temp;
				Help_refresh = true;
				Help();
				Pause_Hide();
				return;
				break;

			case 27: //ESC��
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
	Print(" ��Ϸ��ͣ");
	Cursor(4 * (PLOT_WIDTH + 1) + 1, 20);
	Print(" �˳���Esc");
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
		//���
		string str(WINDOWS_WIDTH, ' ');
		Cursor(0, HELP_INFO_Y);
		cout << str;
		Cursor(0, HELP_INFO_Y);
		if (state == PROCEED) 
		{
			Print(" <������ʾ> ");
			Print(" ֲ����ѡ��\"1/2/3/4/5/6/7/8/9/0\"���ּ� | ���ӣ�\"x\"��");
			Cursor(WINDOWS_WIDTH - 18, 0);
			Print("|��ͣ��Ϸ���ո��|", PAUSE_COLOR);
		}
		else if (state == STORE) 
		{
			Print(" <������ʾ> ");
			Print(" ֲ����ѡ��\"1/2/3/4/5/6/7/8/9/0\"���ּ� | ȷ����ֲ���س��� | ���أ�Esc��");
			Cursor(WINDOWS_WIDTH - 18, 0);
			Print("|��ͣ��Ϸ���ո��|", PAUSE_COLOR);
		}
		else if (state == REMOVE) 
		{
			Print(" <������ʾ> ");
			Print(" ȷ�ϲ������س��� | ���أ�Esc��");
			Cursor(WINDOWS_WIDTH - 18, 0);
			Print("|��ͣ��Ϸ���ո��|", PAUSE_COLOR);
		}
		else if (state == PAUSE) 
		{
			Print(" <��ͣ��> ");
			Cursor(WINDOWS_WIDTH - 18, 0);
			Print("|������Ϸ���ո��|", PAUSE_COLOR);
			Pause_Display();
		}
		Help_refresh = false;
	}
}



void Game::gameover()
{
	system("cls");
	Cursor(WINDOWS_WIDTH / 2 - 8, WINDOWS_HEIGHT / 2 - 1);
	Print("��", FOREGROUND_GREEN);
	Sleep(500);
	Print("ʬ", FOREGROUND_GREEN);
	Sleep(500);
	Print("��");
	Sleep(500);
	Print("��");
	Sleep(500);
	Print("��");
	Sleep(500);
	Print("��");
	Sleep(500);
	Print("��");
	Sleep(500);
	Print("��");
	Sleep(500);
	Print("!");
	Sleep(500);
	Cursor(WINDOWS_WIDTH / 2 - 6, WINDOWS_HEIGHT / 2 + 1);
	cout << "SCORE��" << score << '!';
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
	cout << "SCORE��" << score << '!';
	Cursor(0, WINDOWS_HEIGHT - 2);
	system("pause");
	exit(0);
}


void Game::moveBullet()
{
	list<Bullet*> ::iterator it;
	//ȫ��������ִ���ƶ�
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
	//ȫ��������ִ�����
	for (it = bullets.begin(); it != bullets.end(); it++)
	{
		(*it)->paint();
	}
}