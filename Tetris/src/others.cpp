#include<easyx.h>
#include<fstream>
#include"blocks.h"
#include"others.h"
#include"switch.h"
using namespace std;
void initialscores()//初始状态下对文件进行写入
{
	HWND newwindow = GetHWnd();
	int x = MessageBox(newwindow, "确定要清空分数记录吗?", "提示", MB_OKCANCEL);
	if (x == IDOK)
	{
		ofstream OutScores("data/scores.dat", ios::out | ios::binary);
		scoredata blank;
		for (int i = 0; i < 30; i++)
		{
			OutScores.write(reinterpret_cast<const char*>(&blank), sizeof(scoredata));
		}
		OutScores.close();
	}
}
void save_score()//每种分数上限存十个，没满就加，满了舍弃最小值
{
	int sc = shapes::get_score();
	int md = shapes::get_mode();
	scoredata newdata(md, sc);
	int count = 0;
	ifstream ReadScore("data/scores.dat", ios::in | ios::binary);
	scoredata reader;
	int i = 0;
	while (ReadScore&&!ReadScore.eof())
	{
		ReadScore.read(reinterpret_cast<char*>(&reader), sizeof(scoredata));
		if (i >= md * 10 && i < md * 10 + 10)
		{
			if (reader.lable == -1)
				break;
			count++;
		}
		i++;
		if (i == 30)
			break;
	}
	if (count < 10)//没有满时的情况直接加
	{	
		ofstream OutRecord("data/scores.dat", ios::in | ios::out | ios::binary);
		OutRecord.seekp((md * 10 + count) * sizeof(scoredata));
		OutRecord.write(reinterpret_cast<const char*>(&newdata), sizeof(scoredata));
	}
	if (count == 10)//已经存满10个的情况舍最小
	{
		int count = 0;
		int min = 0;
		int sign = 0;
		while (ReadScore&&!ReadScore.eof())
		{
			if (count >= md * 10 && count < md * 10 + 10)
			{
				scoredata reader;
				ReadScore.read(reinterpret_cast<char*>(&reader), sizeof(scoredata));
				if (reader.score <= min)
				{
					min = reader.score;
					sign = count;
				}
			}
			count++;
		}
		if (min < sc)//判断存档里最小的数据是不是比当前的分数还要小
		{
			ofstream SaveScores("data/scores.dat", ios::in | ios::out | ios::binary);
			SaveScores.seekp(sign * sizeof(scoredata));
			SaveScores.write(reinterpret_cast<const char*>(&newdata), sizeof(scoredata));
			SaveScores.close();
		}
	}		
	ReadScore.close();
}
void sortScores(int* p)
{
	for (int i = 0; i < 10; i++)
	{
		int max = 0;
		int index = 0;
		for (int j = 0; j < 10-i; j++)
		{
			if (p[j] > max)
			{
				max = p[j];
				index = j;
			}
		}
		int temp = p[9 - i];
		p[9 - i] = max;
		p[index] = temp;
	}
}
void select_modes_score()
{
	setbkcolor(WHITE);
	settextcolor(BLACK);
	cleardevice();
	outtextxy(150, 200, "排行榜选择");
	button easy("简单模式", easy_rank);
	button m("普通模式", m_rank);
	button di("困难模式", difficult_rank);
	vector<button> modes;
	modes.push_back(easy);
	modes.push_back(m);
	modes.push_back(di);
	LineButtons rankingmode(150, 300, 50, 100, 90, modes, RGB(255,127,39), RGB(222,231,148));
}
void easy_rank()
{
	ifstream ReadScore("data/scores.dat", ios::in | ios::binary);
	scoredata reader;
	int a[10] = {0};
	int i = 0;
	while (ReadScore && !ReadScore.eof())
	{
		ReadScore.read(reinterpret_cast<char*>(&reader), sizeof(scoredata));
		a[i] = reader.score;
		i++;
		if (i == 10)
			break;
	}
	ReadScore.close();
	sortScores(a);
	int s_x = 150;
	int s_y = 100;
	int d_y = 40;
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, "微软雅黑");
	cleardevice();
	if (a[9] == 0)
	{
		outtextxy(100, 250, "当前暂无任何游戏分数记录!");
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			string sco = to_string(i+1) + ".";
			sco += to_string(a[9-i]);
			const char* info = sco.data();
			outtextxy(s_x, s_y + i * d_y, info);
		}
	}
	button g_b(150, 600, 100, 50, "返回主菜单", go_back, YELLOW, RED);
	g_b.button_clicked_effect();
}
void m_rank()
{
	ifstream ReadScore("data/scores.dat", ios::in | ios::binary);
	scoredata reader;
	int a[10];
	int i = 0;
	while (ReadScore && !ReadScore.eof())
	{
		ReadScore.read(reinterpret_cast<char*>(&reader), sizeof(scoredata));
		if (i >= 10 && i < 20)
			a[i-10] = reader.score;
		i++;
		if (i == 20)
			break;
	}
	ReadScore.close();
	sortScores(a);
	int s_x = 150;
	int s_y = 100;
	int d_y = 40;
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, "微软雅黑");
	cleardevice();
	if (a[9] == 0)
	{
		outtextxy(100, 250, "当前暂无任何游戏分数记录!");
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			string sco = to_string(i + 1) + ".";
			sco += to_string(a[9 - i]);
			const char* info = sco.data();
			outtextxy(s_x, s_y + i * d_y, info);
		}
	}
	button g_b(150, 600, 100, 50, "返回主菜单", go_back, YELLOW, RED);
	g_b.button_clicked_effect();
}
void difficult_rank()
{
	ifstream ReadScore("data/scores.dat", ios::in | ios::binary);
	scoredata reader;
	int a[10];
	int i = 0;
	while (ReadScore && !ReadScore.eof())
	{
		ReadScore.read(reinterpret_cast<char*>(&reader), sizeof(scoredata));
		if (i >= 20 && i < 30)
			a[i - 20] = reader.score;
		i++;
		if (i == 30)
			break;
	}
	ReadScore.close();
	sortScores(a);
	int s_x = 150;
	int s_y = 100;
	int d_y = 40;
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, "微软雅黑");
	cleardevice();
	if (a[9] == 0)
	{
		outtextxy(100, 250, "当前暂无任何游戏分数记录!");
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			string sco = to_string(i + 1) + ".";
			sco += to_string(a[9 - i]);
			const char* info = sco.data();
			outtextxy(s_x, s_y + i * d_y, info);
		}
	}
	button g_b(150, 600, 100, 50, "返回主菜单", go_back, YELLOW, RED);
	g_b.button_clicked_effect();
}
void setmusic()
{
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setfillcolor(YELLOW);
	cleardevice();	
	fillroundrect(150, 550, 150 + 100, 550 + 50, 10, 10);
	outtextxy(153, 560, "返回主菜单");
	funSwitch mainmusic(100, 100, 190, 116, 15);
	outtextxy(130, 50, "主界面音量设置");
	outtextxy(300, 100, "当前状态:");
	funSwitch gamemusic(100, 400, 190, 116, 15);
	outtextxy(130, 350, "游戏界面音量设置");
	outtextxy(300, 400, "当前状态:");
	//funSwitch gamemusic();
	if (mainmusic.state)
		mainmusic.state_on();
	else
		mainmusic.state_off();
	if (gamemusic.state_)
		gamemusic.state_on();
	else
		gamemusic.state_off();
	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.x >= mainmusic.dis_x && msg.x <= mainmusic.dis_x + mainmusic.lo_x && msg.y >= mainmusic.dis_y && msg.y <= mainmusic.dis_y + mainmusic.lo_y)
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					mainmusic.state_change(0);
				}
			}
			else if (msg.x >= gamemusic.dis_x && msg.x <= gamemusic.dis_x + gamemusic.lo_x && msg.y >= gamemusic.dis_y && msg.y <= gamemusic.dis_y + gamemusic.lo_y)
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					gamemusic.state_change(1);
				}
			}
			else if (msg.x >= 150 && msg.x <= 150+100&& msg.y >= 500 && msg.y <= 550+50&&msg.message==WM_LBUTTONDOWN)
			{
				return;
			}
		}
		if (mainmusic.state == 1)
		{
			mciSendString("setaudio main volume to 1000", 0, 0, 0);
			BeginBatchDraw();
			clearroundrect(300, 130, 400, 160, 10, 10);
			outtextxy(300, 130, "开");
			FlushBatchDraw();
			EndBatchDraw();
		}
		else
		{
			mciSendString("setaudio main volume to 0", 0, 0, 0);
			BeginBatchDraw();
			clearroundrect(300, 130, 400, 160, 10, 10);
			outtextxy(300, 130, "关");
			FlushBatchDraw();
			EndBatchDraw();
		}
		if (gamemusic.state_ == 1)
		{
			clearroundrect(300, 430, 400, 460, 10, 10);
			outtextxy(300, 430, "开");
		}
		else
		{
			clearroundrect(300, 430, 400, 460, 10, 10);
			outtextxy(300, 430, "关");
		}
	}
}