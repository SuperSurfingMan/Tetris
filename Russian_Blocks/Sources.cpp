#include"blocks.h"
#include"create_LineButtons.h"
int main()
{
	vector<button> buttons;
	create_main_button(buttons);
	initgraph(400, 710);
	while (1)
	{
		show_main_menu();
		LineButtons main_button(buttons);
	}
	return 0;
}