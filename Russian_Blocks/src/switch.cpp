#include"switch.h"	
int funSwitch::state = 1;
int funSwitch::state_ = 1;
void funSwitch::state_off()
{
	IMAGE close;
	loadimage(&close, "./assets/images/close.jpg", lo_x, lo_y);
	putimage(dis_x, dis_y, &close);
}
void funSwitch::state_on()
{
	IMAGE open;
	loadimage(&open, "./assets/images/open.jpg", lo_x, lo_y);
	putimage(dis_x, dis_y, &open);
}
void funSwitch::switch_on()
{
	state_off();

	IMAGE P1;	IMAGE P2;
	IMAGE P3;	IMAGE P4;
	IMAGE P5;	IMAGE P6;
	IMAGE P7;	IMAGE P8;
	IMAGE P9;	IMAGE P10;
	IMAGE P11;
	loadimage(&P1, "./assets/images/P1.jpg", lo_x, lo_y);
	loadimage(&P2, "./assets/images/P2.jpg", lo_x, lo_y);
	loadimage(&P3, "./assets/images/P3.jpg", lo_x, lo_y);
	loadimage(&P4, "./assets/images/P4.jpg", lo_x, lo_y);
	loadimage(&P5, "./assets/images/P5.jpg", lo_x, lo_y);
	loadimage(&P6, "./assets/images/P6.jpg", lo_x, lo_y);
	loadimage(&P7, "./assets/images/P7.jpg", lo_x, lo_y);
	loadimage(&P8, "./assets/images/P8.jpg", lo_x, lo_y);
	loadimage(&P9, "./assets/images/P9.jpg", lo_x, lo_y);
	loadimage(&P10, "./assets/images/P10.jpg", lo_x, lo_y);
	loadimage(&P11, "./assets/images/P11.jpg", lo_x, lo_y);

	putimage(dis_x, dis_y, &P1);
	Sleep(delay);
	putimage(dis_x, dis_y, &P2);
	Sleep(delay);
	putimage(dis_x, dis_y, &P3);
	Sleep(delay);
	putimage(dis_x, dis_y, &P4);
	Sleep(delay);
	putimage(dis_x, dis_y, &P5);
	Sleep(delay);
	putimage(dis_x, dis_y, &P6);
	Sleep(delay);
	putimage(dis_x, dis_y, &P7);
	Sleep(delay);
	putimage(dis_x, dis_y, &P8);
	Sleep(delay);
	putimage(dis_x, dis_y, &P9);
	Sleep(delay);
	putimage(dis_x, dis_y, &P10);
	Sleep(delay);
	putimage(dis_x, dis_y, &P11);

	state_on();
}
void funSwitch::switch_off()
{
	state_on();
	IMAGE P1;	IMAGE P2;
	IMAGE P3;	IMAGE P4;
	IMAGE P5;	IMAGE P6;
	IMAGE P7;	IMAGE P8;
	loadimage(&P1, "./assets/images/_P1.jpg", lo_x, lo_y);
	loadimage(&P2, "./assets/images/_P2.jpg", lo_x, lo_y);
	loadimage(&P3, "./assets/images/_P3.jpg", lo_x, lo_y);
	loadimage(&P4, "./assets/images/_P4.jpg", lo_x, lo_y);
	loadimage(&P5, "./assets/images/_P5.jpg", lo_x, lo_y);
	loadimage(&P6, "./assets/images/_P6.jpg", lo_x, lo_y);
	loadimage(&P7, "./assets/images/_P7.jpg", lo_x, lo_y);
	loadimage(&P8, "./assets/images/_P8.jpg", lo_x, lo_y);
	putimage(dis_x, dis_y, &P1);
	Sleep(delay);
	putimage(dis_x, dis_y, &P2);
	Sleep(delay);
	putimage(dis_x, dis_y, &P3);
	Sleep(delay);
	putimage(dis_x, dis_y, &P4);
	Sleep(delay);
	putimage(dis_x, dis_y, &P5);
	Sleep(delay);
	putimage(dis_x, dis_y, &P6);
	Sleep(delay);
	putimage(dis_x, dis_y, &P7);
	Sleep(delay);
	putimage(dis_x, dis_y, &P8);

	state_off();
}
void funSwitch::state_change(int n)
{
	if (n == 0)
	{
		if (state == 1)
		{
			switch_off();
			state = 0;
		}
		else
		{
			switch_on();
			state = 1;
		}
	}
	else
	{
		if (state_ == 1)
		{
			switch_off();
			state_ = 0;
		}
		else
		{
			switch_on();
			state_ = 1;
		}
	}
}
int funSwitch::getState()
{
	return state;
}
int funSwitch::getGame()
{
	return state_;
}