#include"buttons.h"
#include<easyx.h>
//start class button
//display a normal button
void button::show_button()
{
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, "微软雅黑");
	setfillcolor(bottom);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextcolor(BLACK);
	const char* button = content.data();
	int tx = x + (w - textwidth(button)) / 2;
	int ty = y + (h - textheight(button)) / 2;
	outtextxy(tx, ty, button);
}
//display a button when being clicked
void button::show_clicked_button()
{
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, "微软雅黑");
	setfillcolor(up);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextcolor(WHITE);
	const char* button = content.data();
	int tx = x + (w - textwidth(button)) / 2;
	int ty = y + (h - textheight(button)) / 2;
	outtextxy(tx, ty, button);
}
//combine the last two functions to make a button's color change when being clicked 
void button::button_clicked_effect()
{
	show_button();
	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.x >= x && msg.x <= x + w && msg.y >= y && msg.y <= y + h)
			{
				show_clicked_button();
				if (msg.message == WM_LBUTTONDOWN)
				{
					func();
					return;
			    }
			}
			else
			{
				show_button();
			}
		}
	}
}
//button constructor
button::button(int _x = 0, int _y = 0, int _w = 1, int _h = 1,string _content = "NULL",void (*fun)()=NULL,COLORREF d = RGB(178, 200, 162),COLORREF p = RGB(153, 255, 135))
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	content = _content;
	func = fun;
	bottom = d;
	up = p;
}
button::button(string _content, void (*fun)())
{
	func = fun;
	content = _content;
}
button::button(string _content, void (*funct)(int), int in)
{
	function = funct;
	content = _content;
	index = in;
}
//end class button
//start class LineButtons,this class creates a line of buttons in the middle of the drawing window or somewhere constructor defines
LineButtons::LineButtons(int s_x,int s_y,int h,int w,int d_y,vector<button>& b)//自定义按键参数
{
	start_x = s_x;
	start_y = s_y;
	height = h;
	width = w;
	delta_y = d_y;
	for (int i = 0; i < b.size(); i++)
	{
		buttons.push_back(b[i]);
	}
	show_button(0);
	on_button();
}
LineButtons::LineButtons(int s_x, int s_y, int h, int w, int d_y, vector<button>& b,COLORREF bot,COLORREF _up)//自定义按键参数及按键颜色
{
	start_x = s_x;
	start_y = s_y;
	height = h;
	width = w;
	delta_y = d_y;
	for (int i = 0; i < b.size(); i++)
	{
		buttons.push_back(b[i]);
	}
	bottom = bot;
	up = _up;
	show_button(0);
	on_button();
}
LineButtons::LineButtons(vector<button>& b)//默认按键位置及颜色
{
	for (int i = 0; i < b.size(); i++)
	{
		buttons.push_back(b[i]);
	}
	show_button(0);
	on_button();
}
void LineButtons::show_button(int n)//通过传入参数同时显示出多个被按下以及未被按下的按键
{
	int x = start_x;
	int y = start_y;
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, "微软雅黑");
	for (int i = 0; i < buttons.size(); i++)
	{
		const char* button = buttons[i].content.data();
		int tx = x + (width - textwidth(button)) / 2;
		int ty = y + (height - textheight(button)) / 2;
		if (i + 1 == n)
		{
			setfillcolor(up);
			settextcolor(BLACK);
		}
		else
		{
			setfillcolor(bottom);
			settextcolor(WHITE);
		}
		solidroundrect(x, y, x + width, y + height, 10, 10);
		outtextxy(tx, ty, button);
		y += delta_y;
	}
}
void LineButtons::on_button()//通过检测鼠标位置，传入不同值动态显示按键效果
{
	show_button(0);
	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{	
			for (int i = 0; i < buttons.size(); i++)
			{
				if (msg.x >= start_x && msg.x <= start_x + width && msg.y >= start_y + i * delta_y && msg.y <= start_y + height + i * delta_y)
				{			
					BeginBatchDraw();
					show_button(i + 1);
					FlushBatchDraw();
					EndBatchDraw();
					if (msg.message == WM_LBUTTONDOWN)
					{
						if (!buttons[i].index)//判断index值,决定是否需要调用button中储存的含参数成员函数，这一点专门为存档而设计
							buttons[i].func();
						else
							buttons[i].function(buttons[i].index);
						return;
					}
				}
			}
		}
	}
}