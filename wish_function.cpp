#include "wish.h"
using namespace std;

extern class User
{
public:
	int UID;
};
extern vector<User>::iterator it_user;

//acquaint_fate相遇之缘，starglitter星辉，primogems原石，intertwined_fate纠缠之缘
int acquaint_fate=0, starglitter=0, primogems=0, intertwined_fate=0;
double probability4[20], probability5[90];
int role_amount4=0, role_amount5=0;
int permanent_amount4=0, permanent_amount5=0;
int role_guarantee4=0, role_guarantee5=0;
int role_pool = NOT_WISH_ROLE;
int ITEM = file_line("all_text\\data.txt");
int ID;
class Items
{
public:
	int ID;
	string name;
	int star;
	string type;
	Items()
	{
		ID = 0;
		name = "";
		star = 0;
		type = "";
	}

}*item = new Items[ITEM];

class Permanent_record
{
public:
	int ID;
	time_t wish_time;
};
vector<Permanent_record>v_permanent_record;

class Role_record
{
public:
	int ID;
	time_t wish_time;
};
vector<Role_record>v_role_record;

class Role_pool
{
public:
	int pool_ID;//自定义的为负数，内置卡池为正数
	string pool_name = "";
	int role5_ID;
	int role4_ID[3];
	static int all_role_pool;
	Role_pool(int role5, int role4_1, int role4_2, int role4_3)
	{
		all_role_pool++;
		pool_ID = all_role_pool;
		/*if (role4_1 == role4_2 || role4_1 == role4_3 || role4_3 == role4_2)
		{
			cout << "陪跑四星重复！" << endl;
			return;
		}*/
		this->role5_ID = role5;
		this->role4_ID[0] = role4_1;
		this->role4_ID[1] = role4_2;
		this->role4_ID[2] = role4_3;
		pool_name += item[role5_ID - 1].name;
		pool_name += " ";
		pool_name += "（陪跑四星：";
		for (int i = 0; i < 3; i++)
		{
			pool_name += item[role4_ID[i] - 1].name;
			pool_name += ",";
		}
		pool_name.pop_back();
		pool_name += "）";
	}

};
int Role_pool::all_role_pool = 0;
vector<Role_pool>v_role_pool;

void addpool()
{
	v_role_pool.push_back(Role_pool(77, 29, 24, 26));
	v_role_pool.push_back(Role_pool(84, 29, 24, 26));
	v_role_pool.push_back(Role_pool(79, 82, 30, 22));
	v_role_pool.push_back(Role_pool(83, 82, 30, 22));
	v_role_pool.push_back(Role_pool(81, 39, 37, 38));
	v_role_pool.push_back(Role_pool(80, 39, 37, 38));
}

void user_resource(int uid)
{
	ID = uid;
	//读取用户资源
	ifstream ifs;
	string str;
	ifs.open("all_text\\User\\" + to_string(ID) + "\\resource.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开错误，用户资源文件不存在" << endl;
		ifs.close();
		system("pause");
		system("exit");
	}
	while (!ifs.eof())
	{
		ifs >> str;
		if (str == "acquaint_fate")
		{
			ifs >> acquaint_fate;
		}
		else if (str == "starglitter")
		{
			ifs >> starglitter;
		}
		else if (str == "primogems")
		{
			ifs >> primogems;
		}
		else if (str == "intertwined_fate")
		{
			ifs >> intertwined_fate;
		}
		else if (str == "role_amount4")
		{
			ifs >> role_amount4;
		}
		else if (str == "role_amount5")
		{
			ifs >> role_amount5;
		}
		else if (str == "permanent_amount4")
		{
			ifs >> permanent_amount4;
		}
		else if (str == "permanent_amount5")
		{
			ifs >> permanent_amount5;
		}
		else if (str == "role_guarantee4")
		{
			ifs >> role_guarantee4;
		}
		else if (str == "role_guarantee5")
		{
			ifs >> role_guarantee5;
		}
		else
		{
			continue;
		}
	}
	ifs.close();
}



int get_random_number(int a, int b)
{
	return (rand() * rand()) % (b - a + 1) + a;
}
bool menu()
{

	addpool();
	int menu_choose;
	while (1)
	{
		cout << "[菜单]" << endl;
		cout << " 1)抽卡" << endl;
		cout << " 2)分析" << endl;
		cout << " 3)充值" << endl;
		cout << " 4)查询" << endl;
		cout << " 5)兑换" << endl;
		cout << " 6)重新登录" << endl;
		cout << "-1)退出游戏" << endl;
		cout << "请输入你的选择：";
		cin >> menu_choose;
		system("cls");
		switch (menu_choose)
		{
		case 1:
			wish_menu();
			break;
		case 2:
			wish_analysis();
			break;
		case 3:
			top_up_primogems();
			break;
		case 4:
			query();
			break;
		case 5:
			exchange();
			break;
		case 6:
			return true;
		case -1:
			return false;
		default:
			cout << "输入错误，请重新输入！" << endl << endl;
			break;

		}
	}
}

//文件的行数，不包括空行
int file_line(string filestr)
{
	int i = 0;
	ifstream ifs;
	string str;
	ifs.open(filestr, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开错误，" << filestr << " 不存在！" << endl;
		return 0;
	}
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str == "")continue;
		i++;
	}
	ifs.close();
	return i;
}
void read_data()
{
	int i;
	ifstream ifs;
	ifs.open("all_text\\data.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开错误，物品数据文件不存在！" << endl;
		ifs.close();
		system("pause");
		system("exit");
	}
	for (i = 0; i < ITEM; i++)
	{
		ifs >> item[i].ID;
		ifs >> item[i].name;
		ifs >> item[i].star;
		ifs >> item[i].type;
	}
	ifs.close();



	for (i = 0; i < 20; i++)
	{
		if (i <= 7)
		{
			probability4[i] = 0.051;
		}
		else if (i == 8)
		{
			probability4[i] = 0.561;
		}
		else
		{
			probability4[i] = 1.0;
		}
	}
	for (i = 0; i < 90; i++)
	{
		probability5[i] = 0.006 + 0.06 * (i - 72);
		if (probability5[i] < 0)
		{
			probability5[i] = 0.006;
		}
		else if (probability5[i] > 1)
		{
			probability5[i] = 1.0;
		}
	}



}


int permanent_item_star()
{
	if (win_or_not(probability5[permanent_amount5]))
	{
		return 5;
	}
	else if (win_or_not(probability4[permanent_amount4]))
	{
		return 4;
	}
	else return 3;
}
int role_item_star()
{
	if (win_or_not(probability5[role_amount5]))
	{
		return 5;
	}
	else if (win_or_not(probability4[role_amount4]))
	{
		return 4;
	}
	else return 3;
}


int win_or_not(double probability)
{
	int a = get_random_number(3, 10000);
	int border = (int)(probability * 10000);
	if (a <= border)
	{
		return 1;
	}
	else return 0;
}
void exchange()
{
	cout << "[兑换]" << endl;
	cout << " 1)原石兑换纠缠之缘" << endl;
	cout << " 2)原石兑换相遇之缘" << endl;
	cout << " 3)无主的星辉兑换纠缠之缘" << endl;
	cout << " 4)无主的星辉兑换相遇之缘" << endl;
	cout << "-1)返回" << endl;
	cout << "请输入你的选择：";
	int choose;
	cin >> choose;
	system("cls");
	switch (choose)
	{
	case 3:
		cout << "兑换完成：将 " << starglitter / 5 * 5 << " 个无主的星辉转换为 " << starglitter / 5 << " 个纠缠之缘。" << endl;
		intertwined_fate += starglitter / 5;
		starglitter %= 5;
		cout << "现持有： " << intertwined_fate << " 个纠缠之缘， " << starglitter << " 个无主的星辉。" << endl << endl;
		break;
	case 4:
		cout << "兑换完成：将 " << starglitter / 5 * 5 << " 个无主的星辉转换为 " << starglitter / 5 << " 个相遇之缘。" << endl;
		acquaint_fate += starglitter / 5;
		starglitter = starglitter % 5;
		cout << "现持有： " << acquaint_fate << " 个相遇之缘， " << starglitter << " 个无主的星辉。" << endl << endl;
		break;
	case 1:
		cout << "兑换完成：将 " << primogems / 160 * 160 << " 个原石转换为 " << primogems / 160 << " 个纠缠之缘。" << endl;
		intertwined_fate += primogems / 160;
		primogems = primogems % 160;
		cout << "现持有： " << intertwined_fate << " 个纠缠之缘， " << primogems << " 个原石。" << endl << endl;
		break;
	case 2:
		cout << "兑换完成：将 " << primogems / 160 * 160 << " 个原石转换为 " << primogems / 160 << " 个相遇之缘。" << endl;
		acquaint_fate += primogems / 160;
		primogems = primogems % 160;
		cout << "现持有： " << acquaint_fate << " 个相遇之缘， " << primogems << " 个原石。" << endl << endl;
		break;
	case -1:
		break;
	default:
		cout << "输入错误，已返回至菜单，请重新输入!" << endl << endl;
		break;
	}

	ofstream ofs;
	ofs.open("all_text\\User\\" + to_string(ID) + "\\resource.txt", ios::out);
	ofs << "primogems " << primogems << endl;
	ofs << "starglitter " << starglitter << endl;
	ofs << "acquaint_fate " << acquaint_fate << endl;
	ofs << "intertwined_fate " << intertwined_fate << endl;
	ofs << "role_amount4 " << role_amount4 << endl;
	ofs << "role_amount5 " << role_amount5 << endl;
	ofs << "permanent_amount4 " << permanent_amount4 << endl;
	ofs << "permanent_amount5 " << permanent_amount5 << endl;
	ofs << "role_guarantee4 " << role_guarantee4 << endl;
	ofs << "role_guarantee5 " << role_guarantee5 << endl;
	ofs.close();

}
void query()
{
	cout << "查询成功！" << endl << endl;
	cout << "纠缠之缘：" << intertwined_fate << endl;
	cout << "相遇之缘：" << acquaint_fate << endl;
	cout << "原石：" << primogems << endl;
	cout << "无主的星辉：" << starglitter << endl;
	cout << endl;
}
void top_up_primogems()
{
	int i;
	cout << " 1)60原石" << endl;
	cout << " 2)300原石" << endl;
	cout << " 3)980原石" << endl;
	cout << " 4)1980原石" << endl;
	cout << " 5)3280原石" << endl;
	cout << " 6)6480原石" << endl;
	cout << " 7)16000原石" << endl;
	cout << "-1)返回" << endl;
	cout << "请输入你要充值的档位：";
	cin >> i;
	system("cls");
	switch (i)
	{
	case 1:
		primogems += 60;
		break;
	case 2:
		primogems += 300;
		break;
	case 3:
		primogems += 980;
		break;
	case 4:
		primogems += 1980;
		break;
	case 5:
		primogems += 3280;
		break;
	case 6:
		primogems += 6480;
		break;
	case 7:
		primogems += 16000;
		break;
	case -1:
		return;
	default:
		system("cls");
		cout << "输入错误，请重新输入！" << endl << endl;
		top_up_primogems();
		break;
	}
	system("cls");
	cout << "成功充值，现在的原石数量为：" << primogems <<"，请继续充值！" << endl << endl;
	top_up_primogems();

	ofstream ofs;
	ofs.open("all_text\\User\\" + to_string(ID) + "\\resource.txt", ios::out);
	ofs << "primogems " << primogems << endl;
	ofs << "starglitter " << starglitter << endl;
	ofs << "acquaint_fate " << acquaint_fate << endl;
	ofs << "intertwined_fate " << intertwined_fate << endl;
	ofs << "role_amount4 " << role_amount4 << endl;
	ofs << "role_amount5 " << role_amount5 << endl;
	ofs << "permanent_amount4 " << permanent_amount4 << endl;
	ofs << "permanent_amount5 " << permanent_amount5 << endl;
	ofs << "role_guarantee4 " << role_guarantee4 << endl;
	ofs << "role_guarantee5 " << role_guarantee5 << endl;
	ofs.close();
}
void wish_menu()
{
	int pool, wish;
	while (true)
	{
		cout << "[抽卡]" << endl;
		cout << " 1)角色池" << endl;
		cout << " 2)武器池（目前尚未开发）" << endl;
		cout << " 3)常驻池" << endl;
		cout << "-1)返回" << endl;
		cout << "请输入你要抽取的卡池：";
		cin >> pool;
		system("cls");
		if (pool == 1)
		{
			while (true)
			{
				if (role_pool == NOT_WISH_ROLE)
				{
					cout << "[卡池选择]" << endl;
					for (vector<Role_pool>::iterator it = v_role_pool.begin(); it != v_role_pool.end(); it++)
					{
						cout << setw(2) << right << it->pool_ID << ")" << it->pool_name << endl;
					}
					cout << " 0)自定义卡池（该功能目前尚未开发）" << endl;
					cout << "-1)返回" << endl;
					cout << "请输入你选择的卡池：";
					cin >> role_pool;
					system("cls");
				}
				if (role_pool >= 1 && role_pool <= v_role_pool.size());
				else if (role_pool == 0)
				{
					cout << "自定义卡池功能尚未开发，请等待！" << endl << endl;
					role_pool = NOT_WISH_ROLE;
					continue;
				}
				else if (role_pool == -1)
				{
					break;
				}
				else
				{
					cout << "输入错误，请重新输入！" << endl;
					role_pool = NOT_WISH_ROLE;
					continue;
				}
				cout << "当前卡池为：" << v_role_pool[role_pool - 1].pool_name << endl << endl;
				cout << " 1)单抽" << endl;
				cout << " 2)十连抽" << endl;
				cout << " 3)更换卡池" << endl;
				cout << "-1)返回" << endl;
				cout << "请输入你的选择：";
				cin >> wish;
				system("cls");
				if (wish == 3)
				{
					role_pool = NOT_WISH_ROLE;
					continue;
				}
				else if (wish == 1)
				{
					if (intertwined_fate <= 0)
					{
						cout << "纠缠之缘不足，是否用 160 个原石兑换！" << endl << endl;
						cout << " 1)是" << endl;
						cout << " 2)否" << endl;
						cout << "请输入你的选择：";
						int j;
						cin >> j;
						system("cls");
						if (j == 1)
						{
							if (primogems < 160)
							{
								cout << "原石不足，请充值!" << endl;
								top_up_primogems();
							}
							else
							{
								primogems -= 160;
								intertwined_fate = 1;
								wish_role(1);
							}
						}
						else if (j == 2)
						{
							break;
						}
						else
						{
							cout << "输入错误！" << endl;
						}
					}
					else
					{
						wish_role(1);
					}
				}
				else if (wish == 2)
				{
					if (intertwined_fate < 10)
					{
						cout << "纠缠之缘不足，是否用 " << 160 * (10 - intertwined_fate) << " 个原石兑换！" << endl << endl;
						cout << " 1)是" << endl;
						cout << " 2)否" << endl;
						cout << "请输入你的选择：";
						int j;
						cin >> j;
						system("cls");
						if (j == 1)
						{
							if (primogems < 160 * (10 - intertwined_fate))
							{
								cout << "原石不足，请充值!" << endl;
								top_up_primogems();
							}
							else
							{
								primogems -= 160 * (10 - intertwined_fate);
								intertwined_fate = 10;
								wish_role(10);
							}
						}
						else if (j == 2)
						{
							break;
						}
						else
						{
							cout << "输入错误！" << endl << endl;
						}
					}
					else
					{
						wish_role(10);
					}
				}
				else if (wish == -1)
				{
					break;
				}
				else
				{
					cout << "输入错误，请重新输入！" << endl;
				}
				ofstream ofs;
				ofs.open("all_text\\User\\" + to_string(ID) + "\\resource.txt", ios::out);
				ofs << "primogems " << primogems << endl;
				ofs << "starglitter " << starglitter << endl;
				ofs << "acquaint_fate " << acquaint_fate << endl;
				ofs << "intertwined_fate " << intertwined_fate << endl;
				ofs << "role_amount4 " << role_amount4 << endl;
				ofs << "role_amount5 " << role_amount5 << endl;
				ofs << "permanent_amount4 " << permanent_amount4 << endl;
				ofs << "permanent_amount5 " << permanent_amount5 << endl;
				ofs << "role_guarantee4 " << role_guarantee4 << endl;
				ofs << "role_guarantee5 " << role_guarantee5 << endl;

				ofs.close();
			}
		}
		else if (pool == 2)
		{
			cout << "武器池尚未开发，请等待！" << endl << endl;
		}
		else if (pool == 3)
		{
			while (true)
			{
				cout << "当前卡池为：常驻池" << endl << endl;
				cout << " 1)单抽" << endl;
				cout << " 2)十连抽" << endl;
				cout << "-1)返回" << endl;
				cout << "请输入你的选择：";
				cin >> wish;
				system("cls");
				if (wish == 1)
				{
					if (acquaint_fate <= 0)
					{
						cout << "相遇之缘不足，是否用 " << 160 * (10 - intertwined_fate) << " 个原石兑换！" << endl << endl;
						cout << " 1)是" << endl;
						cout << " 2)否" << endl;
						cout << "请输入你的选择：";
						int j;
						cin >> j;
						system("cls");
						if (j == 1)
						{
							if (primogems < 160)
							{
								cout << "原石不足，请充值!" << endl;
								top_up_primogems();
							}
							else
							{
								primogems -= 160;
								acquaint_fate = 1;
								wish_permanent(1);
							}
						}
						else if (j == 2)
						{
							break;
						}
						else
						{
							cout << "输入错误！" << endl;
						}
					}
					else
					{
						wish_permanent(1);
					}
				}
				else if (wish == 2)
				{
					if (acquaint_fate < 10)
					{
						cout << "相遇之缘不足，是否用 " << 160 * (10 - acquaint_fate) << " 个原石兑换！" << endl << endl;
						cout << " 1)是" << endl;
						cout << " 2)否" << endl;
						cout << "请输入你的选择：";
						int j;
						cin >> j;
						system("cls");
						if (j == 1)
						{
							if (primogems < 160 * (10 - acquaint_fate))
							{
								cout << "原石不足，请充值!" << endl;
								top_up_primogems();
							}
							else
							{
								primogems -= 160 * (10 - acquaint_fate);
								acquaint_fate = 10;
								wish_permanent(10);
							}
						}
						else if (j == 2)
						{
							break;
						}
						else
						{
							cout << "输入错误！" << endl << endl;
						}
					}
					else
					{
						wish_permanent(10);
					}
				}
				else if (wish == -1)
				{
					break;
				}
				else
				{
					cout << "输入错误，请重新输入！" << endl;
				}
				ofstream ofs;
				ofs.open("all_text\\User\\" + to_string(ID) + "\\resource.txt", ios::out);
				ofs << "primogems " << primogems << endl;
				ofs << "starglitter " << starglitter << endl;
				ofs << "acquaint_fate " << acquaint_fate << endl;
				ofs << "intertwined_fate " << intertwined_fate << endl;
				ofs << "role_amount4 " << role_amount4 << endl;
				ofs << "role_amount5 " << role_amount5 << endl;
				ofs << "permanent_amount4 " << permanent_amount4 << endl;
				ofs << "permanent_amount5 " << permanent_amount5 << endl;
				ofs << "role_guarantee4 " << role_guarantee4 << endl;
				ofs << "role_guarantee5 " << role_guarantee5 << endl;
				ofs.close();
			}
		}
		else if (pool == -1)break;
		else
		{
			cout << "输入错误，请重新输入！" << endl;
		}

	}
}
void wish_permanent(int i)
{
	int num, j, star;
	cout << "---------------" << endl;
	for (j = 0; j < i; j++)
	{
		star = permanent_item_star();
		if (star == 5)
		{
			permanent_amount5 = 0;
			permanent_amount4++;
			num = get_random_number(1, 16);
			cout << "\033[33m";
			wish_outcome(num, 3);
			cout << "（5星）" << endl;
			cout << "\033[0m";

		}
		else if (star == 4)
		{
			permanent_amount4 = 0;
			permanent_amount5++;
			num = get_random_number(17, 63);
			cout << "\033[35m";
			wish_outcome(num, 3);
			cout << "（4星）" << endl;
			cout << "\033[0m";
		}
		else if (star == 3)
		{
			permanent_amount4++;
			permanent_amount5++;
			num = get_random_number(64, 76);
			wish_outcome(num, 3);
			cout << endl;
		}
		acquaint_fate -= 1;
	}
	cout << "---------------" << endl;
	if (i == 1)
	{
		cout << "单抽结束！";
	}
	else if (i == 10)
	{
		cout << "十连抽结束！";
	}
	cout << endl << endl;
}
void wish_role(int i)
{
	int num = 0, j, star, choose;
	cout << "---------------" << endl;
	for (j = 0; j < i; j++)
	{
		star = role_item_star();
		if (star == 5)
		{
			role_amount5 = 0;
			role_amount4++;
			if (role_guarantee5 == 0)
			{
				if (win_or_not(0.5))
				{
					num = v_role_pool[role_pool - 1].role5_ID;
				}
				else
				{
					num = get_random_number(1, 6);
					role_guarantee5 = 1;
				}
			}
			else if (role_guarantee5 == 1)
			{
				num = v_role_pool[role_pool - 1].role5_ID;
				role_guarantee5 = 0;
			}
			cout << "\033[33m";
			wish_outcome(num, 1);
			cout << "（5星）" << endl;
			cout << "\033[0m";
		}
		else if (star == 4)
		{
			role_amount4 = 0;
			role_amount5++;
			if (role_guarantee4 == 0)
			{
				if (win_or_not(0.5))
				{
					num = v_role_pool[role_pool - 1].role4_ID[get_random_number(0, 2)];
				}
				else
				{
					while (true)
					{
						num = get_random_number(1, ITEM);
						if (item[num - 1].star == 4 &&
							(num != v_role_pool[role_pool - 1].role4_ID[0] && num != v_role_pool[role_pool - 1].role4_ID[1] && num != v_role_pool[role_pool - 1].role4_ID[2]))
						{
							break;
						}
					}
					role_guarantee4 = 1;
				}
			}
			else if (role_guarantee4 == 1)
			{
				num = v_role_pool[role_pool - 1].role4_ID[get_random_number(0, 2)];
				role_guarantee4 = 0;
			}
			cout << "\033[35m";
			wish_outcome(num, 1);
			cout << "（4星）" << endl;
			cout << "\033[0m";
		}
		else if (star == 3)
		{
			role_amount4++;
			role_amount5++;
			num = get_random_number(64, 76);
			wish_outcome(num, 1);
			cout << endl;
		}
		intertwined_fate -= 1;
	}
	cout << "---------------" << endl;
	if (i == 1)
	{
		cout << "单抽结束！";
	}
	else if (i == 10)
	{
		cout << "十连抽结束！";
	}
	cout << endl << endl;
}
void wish_analysis()
{
	int choose;
	while (1)
	{
		cout << "[分析]" << endl;
		cout << " 1)抽卡记录" << endl;
		cout << " 2)抽卡数据分析(目前尚未开发)" << endl;
		cout << "-1)返回" << endl;
		cout << "请输入你的选择：";
		cin >> choose;
		system("cls");
		if (choose == 1)
		{
			record();
			break;
		}
		else if (choose == 2)
		{
			data_analysis();
			break;
		}
		else if (choose == -1)
		{
			break;
		}
		else
		{
			cout << "输入错误，请重新输入！" << endl;
		}
	}
}
//1为角色池，2为武器池，3为常驻池
void wish_outcome(int number, int pool)
{
	cout << item[number - 1].name;
	if (pool == 1)
	{
		ofstream ofs;
		ofs.open("all_text\\User\\" + to_string(ID) + "\\role_record.txt", ios::app);
		if (!ofs.is_open())
		{
			cout << "文件打开错误，用户抽卡数据不存在！" << endl;
			return;
		}
		ofs << number<<" " << time(0) << endl;
		ofs.close();

	}
	if (pool == 3)
	{
		ofstream ofs;
		ofs.open("all_text\\User\\" + to_string(ID) + "\\permanent_record.txt", ios::app);
		if (!ofs.is_open())
		{
			cout << "文件打开错误，用户抽卡数据不存在！" << endl<<endl;
			return;
		}
		ofs << number << " " << time(0) << endl;
		ofs.close();
	}
}

void record()
{
	int i, j;
	int itemid;
	time_t itemtime;
	int choose, flag = 0;//flag:0表示小保底，1表示大保底
	while (1)
	{
		cout << "[记录]" << endl;
		cout << " 1)角色池" << endl;
		cout << " 2)武器池（目前未开发）" << endl;
		cout << " 3)常驻池" << endl;
		cout << "-1)返回" << endl;
		cout << "请输入你想要获取抽卡记录的卡池：";
		cin >> choose;
		system("cls");
		if (choose == 1)
		{
			ifstream ifs;
			ifs.open("all_text\\User\\" + to_string(ID) + "\\role_record.txt", ios::in);
			if (!ifs.is_open())
			{
				cout << "文件打开失败，角色抽卡数据文件不存在！" << endl;
				ifs.close();
				system("pause");
				system("exit");
			}
			char c;
			ifs >> c;
			if (ifs.eof())
			{
				cout << "没有角色池的抽卡数据！" << endl << endl;
				ifs.close();
				break;
			}
			ifs.seekg(0, ios::beg);

			cout << "<角色池>" << endl;
			cout << "------------------------------------------------------" << endl;
			cout << "总抽数  星级   物品名           类型    抽取时间" << endl;
			cout << "------------------------------------------------------" << endl;
			for (i = 1, j = 1; !ifs.eof(); i++, j++)
			{
				ifs >> itemid;
				ifs >> itemtime;
				if (item[itemid - 1].star == 5)
				{
					cout << "\033[33m";
				}
				else if (item[itemid - 1].star == 4)
				{
					cout << "\033[35m";
				}
				else
				{
					cout << "\033[0m";
				}
				cout << i << "\t";
				cout << item[itemid- 1].star << "      ";
				cout << item[itemid - 1].name << "\t";
				if (item[itemid - 1].name.size() <= 12)
				{
					cout << "\t";
				}
				cout << item[itemid - 1].type << "\t";
				//输出抽卡时间
				cout.fill('0');
				cout << setw(2) << right << localtime(&itemtime)->tm_mon + 1 << "/" << setw(2) << right << localtime(&itemtime)->tm_mday << " ";
				cout << setw(2) << right << localtime(&itemtime)->tm_hour;
				cout << ":" << setw(2) << right << localtime(&itemtime)->tm_min;
				cout << ":" << setw(2) << right << localtime(&itemtime)->tm_sec << "\t";
				cout.fill(' ');
				if (item[itemid - 1].star == 5 && itemid >= 1 && itemid <= 6 && flag == 0)
				{
					cout << j << "抽\t" << "小保底歪";
					j = 0;
					flag = 1;
				}
				else if (item[itemid - 1].star == 5 && flag == 0)
				{
					cout << j << "抽\t" << "小保底没歪";
					j = 0;
				}
				else if (item[itemid - 1].star == 5 && flag == 1)
				{
					cout << j << "抽\t" << "大保底";
					j = 0;
					flag = 0;
				}
				cout << endl;
			}
			cout << "\033[0m";
			cout << "------------------------------------------------------" << endl;
			ifs.close();
			break;
		}
		else if (choose == 2)
		{
			cout << "武器池尚未开发，请重新输入！" << endl;
		}
		else if (choose == 3)
		{
			ifstream ifs;
			ifs.open("all_text\\User\\" + to_string(ID) + "\\permanent_record.txt", ios::in);
			if (!ifs.is_open())
			{
				cout << "文件打开失败，角色抽卡数据文件不存在！" << endl;
				ifs.close();
				system("pause");
				system("exit");
			}
			if (ifs.eof())
			{
				cout << "没有常驻池的抽卡数据！" << endl << endl;
				ifs.close();
				break;
			}
			ifs.seekg(0, ios::beg);

			cout << "<常驻池>" << endl;
			cout << "------------------------------------------------------" << endl;
			cout << "总抽数  星级   物品名           类型    抽取时间" << endl;
			cout << "------------------------------------------------------" << endl;
			for (i = 1, j = 1; !ifs.eof(); i++, j++)
			{
				ifs >> itemid;
				ifs >> itemtime;
				if (item[itemid - 1].star == 5)
				{
					cout << "\033[33m";
				}
				else if (item[itemid - 1].star == 4)
				{
					cout << "\033[35m";
				}
				else
				{
					cout << "\033[0m";
				}
				cout << i << "\t";
				cout << item[itemid - 1].star << "      ";
				cout << item[itemid - 1].name << "\t";
				if (item[itemid - 1].name.size() <= 12)
				{
					cout << "\t";
				}
				cout << item[itemid - 1].type << "\t";
				//输出抽卡时间
				cout.fill('0');
				cout << setw(2) << right << localtime(&itemtime)->tm_mon + 1 << "/" << setw(2) << right << localtime(&itemtime)->tm_mday << " ";
				cout << setw(2) << right << localtime(&itemtime)->tm_hour;
				cout << ":" << setw(2) << right << localtime(&itemtime)->tm_min;
				cout << ":" << setw(2) << right << localtime(&itemtime)->tm_sec << "\t";
				cout.fill(' ');
				if (item[itemid - 1].star == 5)
				{
					cout << j << "抽";
					j = 0;
				}
				cout << endl;
			}
			cout << "\033[0m";
			cout << "------------------------------------------------------" << endl;
			ifs.close();
			break;
		}
		else if (choose == -1)
		{
			break;
		}
		else
		{
			cout << "输入错误，请重新输入！" << endl << endl;
		}
	}
}
void data_analysis()
{
	int choose;
	cout << "[数据分析]" << endl;
	cout << " 1)角色池" << endl;
	cout << " 2)武器池（目前未开发）" << endl;
	cout << " 3)常驻池" << endl;
	cout << "-1)返回" << endl;
	cout << "请输入你想要分析的卡池：";
	cin >> choose;
	system("cls");
	if (choose == 1)
	{
		ifstream ifs;
		ifs.open("all_text\\User\\" + to_string(ID) + "\\role_record.txt", ios::in);
		if (!ifs.is_open())
		{
			cout << "文件打开错误，角色抽卡文件不存在！" << endl << endl;
			ifs.close();
			system("pause");
			system("exit");
		}
		char c;
		ifs >> c;
		if (ifs.eof())
		{
			cout << "没有角色池的抽卡数据！" << endl << endl;
			ifs.close();
			return;
		}
		ifs.seekg(0, ios::beg);

		double not_crooked=0.0;
		int sum = 0, count_up = 0,temp_sum=0;
		int ITEM_ID, t;
		while (!ifs.eof())
		{
			ifs >> ITEM_ID;
			ifs >> t;
			sum++;
			temp_sum++;
			if (item[ITEM_ID - 1].star == 5&& !(item[ITEM_ID - 1].ID>=0&& item[ITEM_ID - 1].ID<=6))
			{
				count_up++;
				
			}
			else if (item[ITEM_ID - 1].star == 5 && (item[ITEM_ID - 1].ID >= 0 && item[ITEM_ID - 1].ID <= 6))
			{

			}
		}






		ifs.close();
	}
	else if (choose == 2)
	{
		cout << "武器池尚未开发，请重新选择！" << endl << endl;
		data_analysis();
	}
	else if (choose == 3)
	{






	}
	else if (choose == -1)
	{
	}
	else
	{
		cout << "输入错误，请重新输入！" << endl << endl;
		data_analysis();
	}


}