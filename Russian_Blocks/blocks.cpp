#include"shows.h"
#include"blocks.h"
#include"others.h"
#include"switch.h"
#include<easyx.h>
#include<conio.h>
#include<time.h>
#include<string>
#include<fstream>
void start_game()
{
	loadkeys();
	mciSendString("close main", 0, 0, 0);
	mciSendString("open ./gaming.mp3 alias gaming", 0, 0, 0);
	mciSendString("play gaming repeat", 0, 0, 0);
	if (!funSwitch::getGame())
	{
		mciSendString("setaudio gaming volume to 0", 0, 0, 0);
	}
	srand((unsigned int)time(0));
	int late = 0;
	int count = 1;
	shapes* newblock = new block1;
	while (1)
	{
		int nnew = rand();
		if (count == 1)
		{
			late = nnew;		
			count = 0;
			continue;
		}
		shapes::nextshape = nnew%5;
		switch (late % 5)
		{
		case 0:
			newblock = new block1;
			break;
		case 1:
			newblock = new block2;
			break;
		case 2:
			newblock = new block3;
			break;
		case 3:
			newblock = new block4;
			break;
		case 4:
			newblock = new block5;
			break;
		}
		late = nnew;
		newblock->move();
		if (shapes::get_stop())//通过暂停键直接退出
		{
			mciSendString("close gaming", 0, 0, 0);
			delete newblock;
			shapes::reset();
			break;
		}
		if (shapes::game_over())//通过游戏结束判断退出
		{
			mciSendString("close gaming", 0, 0, 0);
			mciSendString("open ./lose.wav alias lose", 0, 0, 0);
			mciSendString("play lose", 0, 0, 0);
			save_score();
			delete newblock;
			shapes::reset();
			HWND hnd = GetHWnd();
			int mess = MessageBox(hnd, "游戏结束！是否返回主菜单？", "提示", MB_OKCANCEL);
			mciSendString("close lose", 0, 0, 0);
			if (mess == IDOK)
				break;
		}
	}
}
//初始化自定义按键
char shapes::keyL = 'a';
char shapes::keyR = 'd';
char shapes::keyLr = 'q';
char shapes::keyRr = 'e';
char shapes::keyFall = 's';
int shapes::load_size = 40;//初始化单个方块大小
int shapes::map[100][100] = { 0 };//初始化存储单元
int shapes::map_x = 10;//初始化方格横向数量
int shapes::map_y = 14;//初始化纵向方格数量
int shapes::delay = 500;//初始化下落延迟
int shapes::score = 0;//初始化分数
int shapes::nextshape = 0;//初始化方块记录数据
int shapes::gamemode = 0;//初始化游戏模式
bool shapes::pause_stop = 0;//初始化暂停键状态
//三种游戏模式，对应不同的方块大小及下落速度
void m_difficult()
{
	shapes::load_size = 20;
	shapes::map_x = 20;
	shapes::map_y = 28;
	shapes::delay = 250;
	shapes::gamemode = 2;
	start_game();
}
void m_medium()
{
	shapes::load_size = 25;
	shapes::map_x = 16;
	shapes::map_y = 23;
	shapes::delay = 360;
	shapes::gamemode = 1;
	start_game();
}
void m_easy()
{
	shapes::load_size = 40;
	shapes::map_x = 10;
	shapes::map_y = 14;
	shapes::delay = 500;
	shapes::gamemode = 0;
	start_game();
}
//储存游戏当前信息
void save_game()
{
	HWND hnd = GetHWnd();
	ifstream ReadRecord("records.dat", ios::in | ios::binary);
	store reader;
	int i = 0;
	while (ReadRecord && !ReadRecord.eof())
	{
		ReadRecord.read(reinterpret_cast<char*>(&reader), sizeof(store));
		if (reader.game_mode == -1)
		{
			break;
		}
		i++;
	}
	ReadRecord.close();
	//找到空位并用i记录
	ofstream OutRecord("records.dat", ios::in | ios::out | ios::binary);
	if (!OutRecord)
	{
		MessageBox(hnd, "打开文件发生错误!", "提示", MB_OK);
		return;
	}
	store newstore(0);
	//i<10表明有空位
	if (i < 10)
	{
		OutRecord.seekp(i*sizeof(store));//让系统向后读取
		OutRecord.write(reinterpret_cast<const char*>(&newstore), sizeof(store));
		OutRecord.close();
		MessageBox(hnd, "保存游戏成功!", "提示", MB_OK);
	}
	//无空位时提示存档空间不足
	else
		MessageBox(hnd, "存档空间已满!", "保存失败", MB_OK);
}
void initialRecord()//初始化存档记录
{
	//写入十条没用的空记录
	ofstream OutRecord("records.dat", ios::out | ios::binary);
	if (!OutRecord)
	{
		abort();
	}
	store blankRecord;
	for (int i = 0; i < 10; ++i)
	{
		OutRecord.write(reinterpret_cast<const char*> (&blankRecord), sizeof(store));
	}
	OutRecord.close();
}
void reload_game(int i)//按下加载游戏之后执行此函数,根据传入参数判断打开哪一个存档
{
	fstream Load("records.dat", ios::in | ios::out | ios::binary);
	HWND hnd = GetHWnd();
	if (!Load)
	{
		MessageBox(hnd, "载入游戏失败!", "发生错误",MB_OK);
		return;
	}
	store load;
	int index = 1;
	while (Load && !Load.eof())
	{			
		Load.read(reinterpret_cast<char*>(&load), sizeof(store));
		if (i == index)
		{
			break;
		}
		index++;
	}
	Load.close();
	shapes::nextshape = load.nextshape;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
			shapes::map[i][j] = load.map[i][j];
	}
	shapes::score = load.score;
	switch (load.game_mode)
	{
	case 0:
		m_easy();
		break;
	case 1:
		m_medium();
		break;
	case 2:
		m_difficult();
		break;
	default:
		MessageBox(hnd, "当前存档为空!", "提示", MB_OK);
		break;
	}
}
void delete_file(int j)//删除指定位置的存档
{
	int i = j - 1;//设计i=j-1原因在于button类中index的特性
	if (i >= 10)
		return;
	store blank;
	HWND hnd = GetHWnd();
	ofstream OutRecord("records.dat", ios::in | ios::out | ios::binary);
	if (!OutRecord)
	{
		MessageBox(hnd, "打开文件发生错误!", "提示", MB_OK);
		return;
	}
	OutRecord.seekp(i * sizeof(store));//读到指定删除位置
	OutRecord.write(reinterpret_cast<const char*>(&blank), sizeof(store));
	OutRecord.close();
	MessageBox(hnd, "删除存档记录成功!", "提示", MB_OK);
}
void key_settings()//用户自定义操作键
{
	fstream openfile("keys.dat", ios::in | ios::out | ios::binary);
	allkeys newkeys;
	openfile.read(reinterpret_cast<char*>(&newkeys), sizeof(allkeys));
	openfile.close();

	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, "微软雅黑");
	setfillcolor(WHITE);
	cleardevice();
	int s_x = 100;
	int s_y = 100;
	int d_y = 50;
	for (int i = 0; i < 5; i++)
	{
		string displ = "当前的";
		switch (i)
		{
		case 0:
			displ += "左移键为:";
			displ += newkeys.L;
			break;
		case 1:
			displ += "右移键为:";
			displ += newkeys.R;
			break;
		case 2:
			displ += "逆时针旋转键为:";
			displ += newkeys.L_r;
			break;
		case 3:
			displ += "顺时针旋转键为:";
			displ += newkeys.R_r;
			break;
		case 4:
			displ += "加速下落键为:";
			displ += newkeys.fall;
			break;
		}
		const char* chars = displ.data();
		outtextxy(s_x, s_y+i*d_y,chars);
	}
	outtextxy(s_x-75, s_y + 5 * d_y, "请输入需要修改的按键(按下回车键以确认)");
	char getkey = '0';
	char keys[6] = "abcde";
	string sences[5] = { "请输入左移键: ","请输入右移键: ","请输入逆时针旋转键: ","请输入顺时针旋转键: ","请输入加速下落键: " };
	for (int i = 0; i < 5; i++)
	{
		while (true)
		{
			const char* please = sences[i].data();
			outtextxy(s_x-80, s_y + (6+i) * d_y,please);
			if (_kbhit())
			{
				getkey = _getch();
				if (getkey == 13)
				{
					string left = "已设置为:";
					left += keys[i];
					const char* sentence = left.data();
					outtextxy(s_x+150, s_y + (6+i) * d_y, sentence);
					break;
				}
				keys[i] = getkey;
				sences[i].pop_back();
				fillroundrect(s_x-80, s_y + (6+i) * d_y, s_x + 300, s_y + (6+i) * d_y + 50,10,10);
				sences[i].push_back(keys[i]);
			}
		}
	}
	allkeys loadkeys(keys[0], keys[1], keys[2], keys[3], keys[4]);
	ofstream defkeys("keys.dat", ios::in | ios::out | ios::binary);
	defkeys.write(reinterpret_cast<const char*>(&loadkeys), sizeof(allkeys));
	defkeys.close();
	HWND hnd = GetHWnd();
	MessageBox(hnd, "已完成按键设置!", "提示", MB_OK);
}
void loadkeys()
{
	fstream openfile("keys.dat", ios::in | ios::out | ios::binary);
	allkeys inkeys;
	openfile.read(reinterpret_cast<char*>(&inkeys), sizeof(allkeys));
	openfile.close();

	shapes::keyL = inkeys.L;
	shapes::keyR = inkeys.R;
	shapes::keyLr = inkeys.L_r;
	shapes::keyRr = inkeys.R_r;
	shapes::keyFall = inkeys.fall;
}