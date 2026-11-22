#pragma once
#include<easyx.h>
#include<vector>
#include<string>
#include"shows.h"
#include"blocks.h"
using namespace std;
class button
{
	friend class LineButtons;
protected:
	int x = 20;
	int y = 20;
	int w = 20;
	int h = 20;
	int index = 0;
	string content;
	void (*func)()= NULL;//无参函数
	void (*function)(int) = NULL;//有参函数
	COLORREF bottom = RGB(117, 250, 141);
	COLORREF up = RGB(221, 255, 226);
public:
	button(int s_x, int s_y, int width, int height, string name, void (*func)(),COLORREF bottom,COLORREF up);
	button(string _content, void (*func)());
	button(string _content, void (*function)(int),int index);
	button() {}
	void show_button();
	void show_clicked_button();
	void button_clicked_effect();
};
class LineButtons
{
private:
	int start_x = 150;
	int start_y = 400;
	int width = 100;
	int height = 50;
	int delta_y = 75;  
	COLORREF bottom = RGB(178, 200, 162);
	COLORREF up = RGB(153, 255, 135);
	vector<button> buttons;
public:
	LineButtons(int s_x, int s_y, int h, int w, int d_y,vector<button>& b,COLORREF bottom,COLORREF up);
	LineButtons(int s_x, int s_y, int h, int w, int d_y, vector<button>& b);
	LineButtons(vector<button>& b);
	void show_button(int n);
	void on_button();
};