#include"blocks.h"
block2::block2()
{
	x1 = startLx - load_size; y1 = startLy;
	x2 = x1 + load_size; y2 = y1;
	x3 = x1; y3 = y1 + load_size;
	x4 = x1 + load_size; y4 = y1 + load_size;
}
void block2::L_move()
{
	if (x1 > 0 && x2 > 0 && x3 > 0 && x4 > 0 && !map[x1 / load_size - 1][y1 / load_size] && !map[x2 / load_size - 1][y2 / load_size] && !map[x3 / load_size - 1][y3 / load_size] && !map[x4 / load_size - 1][y4 / load_size])
	{
		x1 -= load_size; x2 -= load_size; x3 -= load_size; x4 -= load_size;
	}
}
void block2::R_move()
{
	if (x1 < 400 - load_size && x2 < 400 - load_size && x3 < 400 - load_size && x4 < 400 - load_size && !map[x1 / load_size + 1][y1 / load_size] && !map[x2 / load_size + 1][y2 / load_size] && !map[x3 / load_size + 1][y3 / load_size] && !map[x4 / load_size + 1][y4 / load_size])
	{
		x1 += load_size; x2 += load_size; x3 += load_size; x4 += load_size;
	}
}
void block2::L_rotate(){}
void block2::R_rotate(){}
void block2::speed_up()
{
	if (y1 + load_size <= stop && y2 + load_size <= stop && y3 + load_size <= stop && y4 + load_size <= stop && !map[x1 / load_size][y1 / load_size + 1] && !map[x2 / load_size][y2 / load_size + 1] && !map[x3 / load_size][y3 / load_size + 1] && !map[x4 / load_size][y4 / load_size + 1])
	{
		mciSendString("close drop", 0, 0, 0);
		mciSendString("open ./assets/audio/drop.wav alias drop", 0, 0, 0);
		mciSendString("play drop", 0, 0, 0);
		y1 += load_size; y2 += load_size; y3 += load_size; y4 += load_size;
	}
}
bool block2::got_hit()
{
	if (y1 >= stop || y2 >= stop || y3 >= stop || y4 >= stop || map[x1 / load_size][y1 / load_size + 1] || map[x2 / load_size][y2 / load_size + 1] || map[x3 / load_size][y3 / load_size + 1] || map[x4 / load_size][y4 / load_size + 1] || map[x1 / load_size][y1 / load_size] || map[x2 / load_size][y2 / load_size] || map[x3 / load_size][y3 / load_size] || map[x4 / load_size][y4 / load_size])
	{
		return true;
	}
	return false;
}
void block2::putimages()
{
	if (!map[x1 / load_size][y1 / load_size] && !map[x2 / load_size][y2 / load_size] && !map[x3 / load_size][y3 / load_size] && !map[x4 / load_size][y4 / load_size])
	{
		putimage(x1, y1, &block);
		putimage(x2, y2, &block);
		putimage(x3, y3, &block);
		putimage(x4, y4, &block);
	}
}
void block2::refreshmap()
{
	mciSendString("close hit", 0, 0, 0);
	mciSendString("open ./assets/audio/hit.wav alias hit", 0, 0, 0);
	mciSendString("play hit", 0, 0, 0);
	int a1 = x1 / load_size; int b1 = y1 / load_size;
	int a2 = x2 / load_size; int b2 = y2 / load_size;
	int a3 = x3 / load_size; int b3 = y3 / load_size;
	int a4 = x4 / load_size; int b4 = y4 / load_size;
	map[a1][b1] = 1; map[a2][b2] = 1; map[a3][b3] = 1; map[a4][b4] = 1;
}