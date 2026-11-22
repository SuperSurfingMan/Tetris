#include"blocks.h"
block4::block4()
{
	x = startLx;
	y = startLy;
}
void block4::L_move()
{
	if (x > 0 && !map[x / load_size - 1][y / load_size])
	{
		x -= load_size;
	}
}
void block4::R_move()
{
	if (x < 400 - load_size && !map[x / load_size + 1][y / load_size])
	{
		x += load_size;
	}
}
void block4::L_rotate() {}
void block4::R_rotate() {}
void block4::speed_up()
{
	if (y + load_size <= stop && !map[x/load_size][y/load_size+1])
	{
		mciSendString("close drop", 0, 0, 0);
		mciSendString("open ./drop.wav alias drop", 0, 0, 0);
		mciSendString("play drop", 0, 0, 0);
		y += load_size;
	}
}
bool block4::got_hit()
{
	if (y >= stop || map[x / load_size][y / load_size + 1]||map[x/load_size][y/load_size])
	{
		return true;
	}
	return false;
}
void block4::putimages()
{
	if(!map[x/load_size][y/load_size])
		putimage(x, y, &block);
}
void block4::refreshmap()
{		
	mciSendString("close hit", 0, 0, 0);
	mciSendString("open ./hit.wav alias hit", 0, 0, 0);
	mciSendString("play hit", 0, 0, 0);
	int a = x / load_size; int b = y / load_size;
	 map[a][b] = 1;
}