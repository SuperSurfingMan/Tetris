#include"shows.h"
#include"blocks.h"
#include"buttons.h"
#include"create_LineButtons.h"
#include<easyx.h>
#include<vector>
#include<fstream>
#include<mmsystem.h>
#include"switch.h"
#pragma comment(lib,"winmm.lib")
using namespace std;
void show_main_menu()
{
	mciSendString("open ./main_.mp3 alias main", 0, 0, 0);
	//mciSendString("setaudio main volume to 100", 0, 0, 0);
	mciSendString("play main repeat", 0, 0, 0);
	if(funSwitch::getState())
		mciSendString("setaudio main volume to 1000", 0, 0, 0);
	else
		mciSendString("setaudio main volume to 0", 0, 0, 0);

	IMAGE main_bk;
	loadimage(&main_bk, "./new_bbbk.jpg", 400, 710);
	cleardevice();
	putimage(0, 0, &main_bk);
}
void show_maker()
{
	IMAGE settings;
	loadimage(&settings, "./settings.jpg", 400, 710);

	const char* relevant_info = "关于此游戏";
	const char* relevant_name = "俄罗斯方块";
	const char* relevant_data = "软件工程4班 黄超平";
	const char* relevant_version = "时间:2023年5月";
	settextcolor(BLACK);
	settextstyle(25, 0, "微软雅黑");
	cleardevice();

	putimage(0, 0, &settings);
	outtextxy(150, 100, relevant_info);
	outtextxy(150, 200, relevant_name);
	outtextxy(120, 300, relevant_data);
	outtextxy(140, 400, relevant_version);
	button gob(150,550,100,50,"返回主菜单", go_back,RGB(161,251,142),RGB(181,230,29));
	gob.button_clicked_effect();
}
void showGameBk()
{
	IMAGE bkPicture;
	loadimage(&bkPicture, "./wooden_bk.png", 400, 710);
	cleardevice();
	putimage(0, 0, &bkPicture);
}
void show_score()//显示游戏中的实时分数
{
	const int r_x = 10;
	const int r_y = 590;
	const int width = 115;
	const int height = 60;
	const int d_y = 25;

	int a = shapes::get_score();
	char score[10] = "\0";
	_itoa_s(a,score,10);
	setfillcolor(RGB(117, 250, 141));
	solidroundrect(r_x, r_y, r_x + width, r_y + height, 10, 10);
	setbkmode(TRANSPARENT);

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	strcpy_s(f.lfFaceName, "微软雅黑");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(25,0,"微软雅黑");
	int tx = r_x + (width - textwidth(score)) / 2;
	int ty = r_y + (height - textheight(score)) / 2;

	settextcolor(BLACK);
	outtextxy(r_x, r_y-d_y, "当前分数:");
	outtextxy(tx, ty, score);
}
void show_coming_blocks(int n)//显示下一个方块
{
	IMAGE c_block;
	loadimage(&c_block, "./g_block.jpg", 20, 20);
	const int c_x = 180;
	const int c_y = 590;
	const int width = 115;
	const int height = 60;

	int beginX = c_x + 10;
	int beginY = c_y + 15;
	int loader = 20;

	settextstyle(0, 0, "微软雅黑");
	outtextxy(c_x-30, c_y - 25, "下一个方块:");
	setfillcolor(RGB(255, 253, 85));
	fillroundrect(c_x-30, c_y, c_x + width-30, c_y + height,10,10);
	switch (n)
	{
	case 0:
		putimage(beginX, beginY, &c_block);
		putimage(beginX, beginY + loader, &c_block);
		putimage(beginX - loader, beginY + loader, &c_block);
		putimage(beginX + loader, beginY + loader, &c_block);
		break;
	case 1:
		putimage(beginX, beginY, &c_block);
		putimage(beginX + loader, beginY, &c_block);
		putimage(beginX, beginY + loader, &c_block);
		putimage(beginX + loader, beginY + loader, &c_block);
		break;
	case 2:
		putimage(beginX, beginY, &c_block);
		putimage(beginX - loader, beginY, &c_block);
		putimage(beginX + loader, beginY, &c_block);
		putimage(beginX + 2* loader, beginY, &c_block);
		break;
	case 3:
		putimage(beginX, beginY, &c_block);
		break;
	case 4:
		putimage(beginX, beginY, &c_block);
		putimage(beginX - loader, beginY, &c_block);
		putimage(beginX + loader, beginY, &c_block);
		putimage(beginX + loader, beginY + loader, &c_block);
		break;
	}
}
void settings()//设置界面
{
	IMAGE settings;
	loadimage(&settings, "./settings.jpg", 400, 710);
	cleardevice();
	putimage(0, 0, &settings);

	vector<button>set;
	for_set(set);
	LineButtons setallthing(150, 150, 50, 120, 100, set, RGB(237, 28, 36), YELLOW);
}
void before_start()//选择游戏模式，新游戏或载入存档
{
	IMAGE settings;
	loadimage(&settings, "./settings.jpg", 400, 710);
	cleardevice();
	putimage(0, 0, &settings);
	vector<button> game;
	game_setting_button(game);
	LineButtons game_mode(150, 200, 50, 120, 150, game,RGB(240,134,80),RGB(115,251,253));
}
void go_back() {}//空函数，实现返回
void game_pause(int p)//展示游戏进行时停止键的按键效果
{
	if (p == 0)
	{
		IMAGE menu;
		loadimage(&menu, "./pause.png", 50, 50);
		putimage(320, 600, &menu);
	}
	else
	{
		IMAGE menu;
		loadimage(&menu, "./pause2.png", 50, 50);
		putimage(320, 600, &menu);
	}
}
void pausing_game()//游戏暂停状态下的界面
{
	IMAGE PAUSE;
	loadimage(&PAUSE, "./PAUSE_.png", 300, 500);
	putimage(50, 50, &PAUSE);
	vector<button> pause;
	pause_button(pause);
	LineButtons pausing(125, 170, 70, 150, 100, pause, RGB(25, 162, 255), RGB(255, 235, 154));
}
void gob_main()//游戏进行时直接回到主界面
{
	HWND hnd = GetHWnd();
	int mess = MessageBox(hnd, "确定要返回主菜单吗？(该操作不会自动保存当前游戏)", "提示", MB_OKCANCEL);
	if(mess==IDOK)
		shapes::pause_stop = 1;
}
void save_and_back()
{
	HWND hnd = GetHWnd();
	int a = MessageBox(hnd, "若存储空间已满将直接返回主菜单，确定要退出吗?", "提示",MB_OKCANCEL);
	if (a == IDOK)
	{
		save_game();
		shapes::pause_stop = 1;
	}
}
void detail_load()//载入存档，进入存档信息界面
{
	ifstream Load("records.dat", ios::in | ios::out | ios::binary);
	HWND hnd = GetHWnd();
	if (!Load)
	{
		MessageBox(hnd, "发生错误!", "提示", MB_OK);
		return;
	}
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, "微软雅黑");
	cleardevice();
	button SCORES[10];
	vector<button> loader;
	store load;
	int i = 0;
    while(Load&&!Load.eof())
	{
		string allinfo;
		Load.read(reinterpret_cast<char*>(&load), sizeof(store));
		if (load.game_mode == -1)
		{
			allinfo = "空";
		}
		else
		{
			string s = "当前分数:" + to_string(load.score);
			string m = "游戏模式:";
			switch (load.game_mode)
			{
			case 0:
				m += "简单";
				break;
			case 1:
				m += "一般";
				break;
			case 2:
				m += "困难";
				break;
			}
			allinfo = m + "    " + s;
		}
		SCORES[i] = button(allinfo, reload_game, i+1);
		loader.push_back(SCORES[i]);
		i++;
		if (i == 10)
			break;
	}
	Load.close();
	button gbm("返回主菜单", go_back);
	loader.push_back(gbm);
	outtextxy(140, 25, "所有存档信息");
	outtextxy(90, 60, "单击以载入存档并进入游戏");
	LineButtons loading(0, 100, 50, 400, 50, loader, RGB(42,219,0), RGB(248,255,190));
}
void select_mode()//选择游戏模式界面
{
	IMAGE settings;
	loadimage(&settings, "./settings.jpg", 400, 710);
	cleardevice();
	putimage(0, 0, &settings);

	vector<button> set_buttons;
	select_mode_buttons(set_buttons);
	LineButtons setButton(150, 100, 50, 100, 120, set_buttons, RGB(235, 51, 36), RGB(255, 233, 53));
}
void manage_file()
{
	ifstream Load("records.dat", ios::in | ios::out | ios::binary);
	HWND hnd = GetHWnd();
	if (!Load)
	{
		MessageBox(hnd, "发生错误!", "提示", MB_OK);
		return;
	}
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, "微软雅黑");
	cleardevice();
	int s_x = 20;
	int s_y = 100;
	int d_y = 50;
	button SCORES[10];
	vector<button> loader;
	store load;
	int i = 0;
	while (Load && !Load.eof())
	{
		string allinfo;
		Load.read(reinterpret_cast<char*>(&load), sizeof(store));
		if (load.game_mode == -1)
		{
			allinfo = "空";
		}
		else
		{
			string s = "当前分数:" + to_string(load.score);
			string m = "游戏模式:";
			switch (load.game_mode)
			{
			case 0:
				m += "简单";
				break;
			case 1:
				m += "一般";
				break;
			case 2:
				m += "困难";
				break;
			}
			allinfo = m + "  " + s;
		}
		const char* infos = allinfo.data();
		outtextxy(s_x, s_y+ d_y * i, infos);
		SCORES[i] = button("删除", delete_file, i+1);
		loader.push_back(SCORES[i]);
		i++;
		if (i == 10)
			break;
	}
	Load.close();
	outtextxy(s_x, s_y + d_y * 10, "该操作将清除以上所有游戏记录!");
	button deleteALL("清空存档", initialRecord);
	button gbm("返回主菜单", go_back);
	loader.push_back(deleteALL);
	loader.push_back(gbm);
	outtextxy(140, 25, "所有存档信息");
	LineButtons loading(300, s_y, 40, 100, 50, loader, RGB(237, 28, 36), RGB(255, 242, 0));
}
void initialkeys()
{
	ofstream OutScores("keys.dat", ios::out | ios::binary);
	allkeys blank;
	OutScores.write(reinterpret_cast<const char*>(&blank), sizeof(allkeys));
	OutScores.close();
}
