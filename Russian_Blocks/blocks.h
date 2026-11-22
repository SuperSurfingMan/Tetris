#pragma once
#include<conio.h>
#include<easyx.h>
#include<vector>
#include"shows.h"
#include"buttons.h"
void start_game();
void m_difficult();
void m_medium();
void m_easy();
void save_game();
void initialRecord();
void reload_game(int);//即将进入游戏界面
void delete_file(int);
void key_settings();
void loadkeys();
class shapes
{
	friend void reload_game(int);
	friend void m_difficult();
	friend void m_medium();
	friend void m_easy();
	friend void gob_main();
	friend void save_and_back();
	friend void loadkeys();
	friend class store;
protected:
	IMAGE block;
	shapes()
	{
		loadimage(&block, "./g_block.jpg", load_size, load_size);
	}
	//创建单个方块,选择需要导入的方块图片
	static int load_size;//设置方块的实际分辨率
	int startLx = 4 * load_size;
	int startLy = 0;
	static char keyL;
	static char keyR;
	static char keyLr;
	static char keyRr;
	static char keyFall;
	//设置方块下落的初始位置
	static int map_x;
	static int map_y;
	static int delay;
	//设置map的大小,在block.cpp中对其进行了初始化
	const int stop = (map_y - 1) * load_size;
	//设置停止线的位置
	static int map[100][100];
	//此处的100不是真实大小，可便于后续修改地图大小
	static int score;
	//设置计分
	static int gamemode;
	int pause = 0;//暂停键的状态
	static bool pause_stop;//判定是否需要返回主菜单
	virtual void L_move() = 0;
	virtual void R_move() = 0;
	virtual void L_rotate() = 0;
	virtual void R_rotate() = 0;
	virtual void speed_up() = 0;
	virtual bool got_hit() = 0;
	virtual void putimages() = 0;
	virtual void refreshmap() = 0;
	//编写子类虚函数,这包括了左移、右移、左转、右转、加速、碰撞判定、画面刷新
	void Line_clear()
	{
		int cls = 0;
		for (int j = 0; j < map_y; j++)
		{
			int count = 0;
			for (int i = 0; i < map_x; i++)
			{
				if (map[i][j] == 1)
					count++;
			}
			if (count == map_x)
			{
				cls++;
				mciSendString("close clear", 0, 0, 0);
				mciSendString("open ./clear.wav alias clear", 0, 0, 0);
				mciSendString("play clear", 0, 0, 0);
				for (int i = j; i >= 0; i--)
				{
					for (int z = 0; z < map_x; z++)
					{
						if (i > 0)
							map[z][i] = map[z][i - 1];
					}
				}
			}
		}
		score += 100 * cls * cls;
	}
	//当满足方块相消条件时分数增加:消除行数平方乘以100,并自动下移方块
public:
	static int nextshape;//记录下一个方块
	void move()
	{
		ExMessage msg;
		int t = 0;
		const char Lmove = keyL;
		bool check = false;
		while (1)
		{
			if (peekmessage(&msg, EX_MOUSE))
			{
				if (msg.x > 320 && msg.x < 320 + 100 && msg.y>600 && msg.y < 600 + 50)
				{
					pause = 1;
					if (msg.message == WM_LBUTTONDOWN)
					{			
						pausing_game();
						if (shapes::get_stop())
							break;
					}
				}
				else
					pause = 0;
			}
			int newtime = GetTickCount();
			if (newtime - t >= delay)
			{
				t = newtime;
				if (check)
				{
					refreshmap();
					break;
				}
				speed_up();
			}
			current_loc();
			if (_kbhit())
			{
				char key = _getch();
				if (key == keyFall)
				{
					speed_up();
					current_loc();
				}
				else if (key == keyL)
				{
					L_move();
					current_loc();
				}
				else if (key == keyR)
				{
					R_move();
					current_loc();
				}
				else if (key == keyLr)
				{
					L_rotate();
					current_loc();
				}
				else if (key == keyRr)
				{
					R_rotate();
					current_loc();
				}
			}
			if (got_hit())
				check = true;
			else
				check = false;
		}
	}
	//主要的执行函数
	void show_map()
	{
		IMAGE map_block;
		loadimage(&map_block, "./b_block.jpg", load_size, load_size);//显示蓝色的方块
		for (int i = 0; i < map_x; i++)
		{
			for (int j = 0; j < map_y; j++)
			{
				if (map[i][j] == 1)
				{
					putimage(i * load_size, j * load_size, &map_block);
				}
			}
		}
	}
	//显示已定格的方块
	static bool game_over()
	{
		for (int i = 0; i < map_x; i++)
		{
			if (map[i][0])
				return true;
		}
		return false;
	}
	//判定游戏结束
	static void reset()
	{
		for (int i = 0; i < map_x; i++)
		{
			for (int j = 0; j < map_y; j++)
			{
				map[i][j] = 0;
			}
		}
		score = 0;
		pause_stop = 0;
	}
	//重置游戏内的相关数据+
	static int get_score()
	{
		return score;
	}
	//获取当前分数
	static int get_mode()
	{
		return gamemode;
	}
	//获取游戏模式
	static bool get_stop()
	{
		return pause_stop;
	}
	//获取退出值
	void current_loc()
	{
		Line_clear();
		BeginBatchDraw();
		showGameBk();
		show_map();
		putimages();
		show_score();
		show_coming_blocks(nextshape);
		game_pause(pause);
		FlushBatchDraw();
		EndBatchDraw();
	}
	//显示游戏进行时需要显示的所有画面信息
};
class store//储存游戏分数用以显示排行榜
{
	friend void reload_game(int);
	friend void detail_load();
	friend void save_game();
	friend void manage_file();
private:
	int score = 0;
	int map[100][100] = {0};
	int game_mode = -1;
	int nextshape = 0;
public:
	store() {}
	store(int)
	{
		score = shapes::score;
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
				map[i][j] = shapes::map[i][j];
		}
		game_mode = shapes::gamemode;
		nextshape = shapes::nextshape;
	}
};
class allkeys
{
	friend void key_settings();
	friend void loadkeys();
private:
	char L = 'a';
	char R = 'd';
	char L_r = 'q';
	char R_r = 'e';
	char fall = 's';
public:
	allkeys() {}
	allkeys(char left_move, char right_move, char left_rotate, char right_rotate, char Fall)
	{
		L = left_move;
		R = right_move;
		L_r = left_rotate;
		R_r = right_rotate;
		fall = Fall;
	}
};
//开始编写T形方块类
class block1 :public shapes
{
private:
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
	int s_x, s_y;//设置这两个数据是为了便于这种图形实现旋转功能
public:
	block1();
	~block1() { delete this; }
	void L_move();
	void R_move();
	void L_rotate();
	void R_rotate();
	void speed_up();
	bool got_hit();
	void putimages();
	void refreshmap();
};
//由四个方块构成的一个大正方形方块
class block2 :public shapes
{
private:
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
public:
	block2();
	~block2() { delete this; }
	void L_move();
	void R_move();
	void L_rotate();
	void R_rotate();
	void speed_up();
	bool got_hit();
	void putimages();
	void refreshmap();
};
//条形方块类,长4格
class block3 :public shapes
{
private:
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
	int state;
public:
	block3();
	~block3() { delete this; }
	void L_move();
	void R_move();
	void L_rotate();
	void R_rotate();
	void speed_up();
	bool got_hit();
	void putimages();
	void refreshmap();
};
//只有一个方块的类
class block4 :public shapes
{
private:
	int x, y;
public:
	block4();
	~block4() { delete this; }
	void L_move();
	void R_move();
	void L_rotate();
	void R_rotate();
	void speed_up();
	bool got_hit();
	void putimages();
	void refreshmap();
};
//L形的方块
class block5 : public shapes
{
private:
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
	int state;
public:
	block5();
	~block5() { delete this; }
	void L_move();
	void R_move();
	void c_state(int n);
	void L_rotate();
	void R_rotate();
	void speed_up();
	bool got_hit();
	void putimages();
	void refreshmap();
};