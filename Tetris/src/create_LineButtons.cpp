#include"create_LineButtons.h"
#include"shows.h"
#include"others.h"
void create_main_button(vector<button>& b)
{
	button a("开始游戏", before_start);
	button b_("排行榜", select_modes_score);
	button c("设置", settings);
	button d("关于", show_maker);

	b.push_back(a);
	b.push_back(b_);
	b.push_back(c);
	b.push_back(d);
}
//for game settings 
void game_setting_button(vector<button>& g)
{
	button a("新游戏", select_mode);
	button b("载入存档", detail_load);
	button o("返回主菜单", go_back);

	g.push_back(a);
	g.push_back(b);
	g.push_back(o);
}
void for_set(vector<button>& s)
{
	button a("存档管理", manage_file);
	button b("清空分数记录", initialscores);
	button c("按键设置", key_settings);
	button d("音乐设置", setmusic);
	button e("返回主菜单", go_back);

	s.push_back(a);
	s.push_back(b);
	s.push_back(c);
	s.push_back(d);
	s.push_back(e);
}
void select_mode_buttons(vector<button>& s)
{
	button a("困难", m_difficult);
	button b("一般", m_medium);
	button c("简单", m_easy);
	button o("返回主菜单", go_back);

	s.push_back(a);
	s.push_back(b);
	s.push_back(c);
	s.push_back(o);
}
void pause_button(vector<button>& p)
{
	button a("保存当前游戏", save_game);
	button b("返回主菜单", gob_main);
	button c("返回当前游戏", go_back);
	button d("保存并返回主菜单", save_and_back);

	p.push_back(a);
	p.push_back(b);
	p.push_back(c);
	p.push_back(d);
}