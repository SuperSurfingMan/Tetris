#pragma once
#include<easyx.h>
#include"others.h"
//图片载入分辨率设置
////此gif原有分辨率为190*116
//const int lo_x = 82;
//const int lo_y = 50;
////图片载入位置设置
//const int dis_x = 1;
//const int dis_y = 1;
////延迟设置(ms)
//const int delay = 15;
class funSwitch
{
	friend void setmusic();
private:
	int lo_x = 82;
	int lo_y = 50;
	int dis_x = 50;
	int dis_y = 100;
	int delay = 15;
	static int state;
	static int state_;
public:
	funSwitch() {}
	funSwitch(int load_x, int load_y, int pixel_x, int pixel_y, int _delay)
	{
		lo_x = pixel_x;
		lo_y = pixel_y;
		dis_x = load_x;
		dis_y = load_y;
		delay = _delay;
	}
	void switch_on();
	void switch_off();
	void state_on();
	void state_off();
	void state_change(int);
	static int getState();
	static int getGame();
};