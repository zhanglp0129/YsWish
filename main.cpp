#include<stdlib.h>
#include "wish.h"
#include"cmd_login.hpp"

int main()
{
	system("chcp 65001");
	system("cls");
	//Login();
	read_user();
	read_data();
	if (!read_log())
	{
	relogin:
		system("cls > all_text\\login.log");
		login_menu();
	}

	string str;
	str = "title UserName: ";
	str += it_user->name;
	const char* s = data(str);
	system(s);
	user_resource(it_user->UID);
	srand((unsigned int)time(0));
	if (menu())
	{
		goto relogin;
	}
	return 0;
}
