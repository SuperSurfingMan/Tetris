#pragma once
void initialscores();
void save_score();
void sortScores(int*);
void select_modes_score();
void easy_rank();
void m_rank();
void difficult_rank();
void setmusic();
class scoredata
{
	friend void save_score();
	friend void easy_rank();
	friend void m_rank();
	friend void difficult_rank();
private:
	int lable = -1;//判断此数据是哪个游戏模式下的，默认无意义
	int score = 0;//数据主体
public:
	scoredata(){}
	scoredata(int l, int s)
	{
		lable = l;
		score = s;
	}
};
