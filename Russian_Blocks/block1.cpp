#include"blocks.h"
block1::block1()
{
	x1 = startLx; y1 = startLy;
	x2 = x1; y2 = y1 + load_size;
	x3 = x1 - load_size; y3 = y1 + load_size;
	x4 = x1 + load_size; y4 = y1 + load_size;
	s_x = x1; s_y = y1 + 2 * load_size;
}
void block1::L_move()
{
	if (x1 > 0 && x2 > 0 && x3 > 0 && x4 > 0 && !map[x1 / load_size - 1][y1 / load_size] && !map[x2 / load_size - 1][y2 / load_size] && !map[x3 / load_size - 1][y3 / load_size] && !map[x4 / load_size - 1][y4 / load_size])
	{
		x1 -= load_size; x2 -= load_size; x3 -= load_size; x4 -= load_size; s_x -= load_size;
	}
}
void block1::R_move()
{
	if (x1 < 400 - load_size && x2 < 400 - load_size && x3 < 400 - load_size && x4 < 400 - load_size && !map[x1 / load_size + 1][y1 / load_size] && !map[x2 / load_size + 1][y2 / load_size] && !map[x3 / load_size + 1][y3 / load_size] && !map[x4 / load_size + 1][y4 / load_size])
	{
		x1 += load_size; x2 += load_size; x3 += load_size; x4 += load_size; s_x += load_size;
	}
}
void block1::L_rotate()
{
	if (!((x4 == 400 - load_size && x3 == 400 - load_size) || (x3 == 0 && x4 == 0) || map[s_x / load_size][s_y / load_size]))
	{
		int temp1 = x3; int temp2 = y3;
		x3 = s_x; y3 = s_y;
		s_x = x4; s_y = y4;
		x4 = x1; y4 = y1;
		x1 = temp1; y1 = temp2;
	}
}
void block1::R_rotate()
{
	if (!((x4 == 400 - load_size && x3 == 400 - load_size) || (x3 == 0 && x4 == 0)||map[s_x/load_size][s_y/load_size]))
	{
		int temp1 = x4; int temp2 = y4;
		x4 = s_x; y4 = s_y;
		s_x = x3; s_y = y3;
		x3 = x1; y3 = y1;
		x1 = temp1; y1 = temp2;
	}
}
void block1::speed_up()
{	
	if (y1 + load_size <= stop && y2 + load_size <= stop && y3 + load_size <= stop && y4 + load_size <= stop && !map[x1 / load_size][y1 / load_size + 1] && !map[x2 / load_size][y2 / load_size + 1] && !map[x3 / load_size][y3 / load_size + 1] && !map[x4 / load_size][y4 / load_size + 1])
	{
		mciSendString("close drop", 0, 0, 0);
		mciSendString("open ./drop.wav alias drop", 0, 0, 0);
		mciSendString("play drop", 0, 0, 0);
		y1 += load_size; y2 += load_size; y3 += load_size; y4 += load_size; s_y += load_size;
	}
}
bool block1::got_hit()
{
	if (y1 >= stop || y2 >= stop || y3 >= stop || y4 >= stop || map[x1 / load_size][y1 / load_size + 1] || map[x2 / load_size][y2 / load_size + 1] || map[x3 / load_size][y3 / load_size + 1] || map[x4 / load_size][y4 / load_size + 1]|| map[x1 / load_size][y1 / load_size] || map[x2 / load_size][y2 / load_size] || map[x3 / load_size][y3 / load_size] || map[x4 / load_size][y4 / load_size])
	{
		return true;
	}
	return false;
}
void block1::putimages()
{ 
	if (!map[x1 / load_size][y1 / load_size] && !map[x2 / load_size][y2 / load_size] && !map[x3 / load_size][y3 / load_size] && !map[x4 / load_size][y4 / load_size])
	{
		putimage(x1, y1, &block);
		putimage(x2, y2, &block);
		putimage(x3, y3, &block);
		putimage(x4, y4, &block);
	}
}
void block1::refreshmap()
{		
	mciSendString("close hit", 0, 0, 0);
	mciSendString("open ./hit.wav alias hit", 0, 0, 0);
	mciSendString("play hit", 0, 0, 0);
	int a1 = x1 / load_size; int b1 = y1 / load_size;
	int a2 = x2 / load_size; int b2 = y2 / load_size;
	int a3 = x3 / load_size; int b3 = y3 / load_size;
	int a4 = x4 / load_size; int b4 = y4 / load_size;
	map[a1][b1] = 1; map[a2][b2] = 1; map[a3][b3] = 1; map[a4][b4] = 1;
}