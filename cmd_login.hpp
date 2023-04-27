#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include<algorithm>
#include<fstream>
#include<ctime>
#include<list>
#include"Md5.hpp"

//定义常量
#define NO_PASSWORD INT_MIN

//保证只定义一次
#ifndef _CMD_LOGIN_HPP_
#define _CMD_LOGIN_HPP_

//类的声明
class User;

//函数声明
bool login();
void read_user();
void login_menu();
void reg();		//注册
void recover_password();
void logout();		//注销
int kind_char(string str);
bool read_log();

#endif


using namespace std;

//定义全局变量
list<User>l_user;
list<User>::iterator it_user=l_user.end();

class User
{
public:
	int UID;
	string name;
	string md5_password;
	//string email;
	//long long phone;
	User();
	User(string _name);
	User(int _UID, string _name, string _password);
	bool operator==(const User& _user);		//匹配账号
};

//函数实现
User::User()
{
	this->UID = 0;
	this->name = "";
	this->md5_password = "";
	//this->email = "";
	//this->phone = 0;
}
User::User(string _name)
{
	this->UID = 0;
	this->md5_password = "";
	this->name = _name;
}
User::User(int _UID, string _name, string _password)
{
	this->UID = _UID;
	this->name = _name;
	this->md5_password = _password;
}
bool User::operator==(const User& _user)//匹配账号
{
	if (this->name == _user.name)return true;
	else return false;
}

bool read_log()
{
	ifstream ifs;
	ifs.open("all_text\\login.log", ios::in);
	if (!ifs.is_open())
	{
		return false;
	}
	char c;
	ifs >> c;
	if (ifs.eof())
	{
		ifs.close();
		return false;
	}
	ifs.seekg(0, ios::beg);

	string temp = "";
	int log_ID = 0;
	string log_name = "";
	time_t log_time = 0;
	string signature = "";
	while (!ifs.eof())
	{
		ifs >> temp;
		if (temp == "UID")
		{
			ifs >> log_ID;
		}
		else if (temp == "name")
		{
			ifs >> log_name;
		}
		else if (temp == "logintime")
		{
			ifs >> log_time;
		}
		else if (temp == "signature")
		{
			ifs >> signature;
		}
		else
		{
			cout << "登录日志失效，请重新登录！" << endl << endl;
			ifs.close();
			return false;
		}
	}
	ifs.close();

	if (log_time + 7 * 24 * 3600 < time(0))
	{
		cout << "登录日志过期，请重新登录！" << endl << endl;
		return false;
	}
	it_user = find(l_user.begin(), l_user.end(), User(log_name));

	//验证加密签名
	string str;
	MD5 md5;
	str = md5.encode(to_string(it_user->UID));
	str += it_user->name;
	str = md5.encode(str);
	str += md5.encode(it_user->md5_password);
	str = md5.encode(str);

	if ((log_ID == it_user->UID) && signature == str)
	{
		cout << "欢迎回来！" << endl << endl;

		ofstream ofs;
		ofs.open("all_text\\login.log", ios::out);
		ofs << "UID " << log_ID << endl;
		ofs << "name " << log_name << endl;
		ofs << "logintime " << time(0) << endl;
		ofs << "signature " << str << endl;
		ofs.close();

		return true;
	}
	else
	{
		cout << "登录日志失效，请重新登录！" << endl << endl;
		return false;
	}
}

void login_menu()
{

	int choose;
	system("title Menu");
	cout << " 1)登录" << endl;
	cout << " 2)注册" << endl;
	cout << " 3)找回密码" << endl;
	//cout << " 4)注销账户" << endl;
	cout << "-1)退出游戏" << endl;
	cout << "请输入你的选择：";
	cin >> choose;
	system("cls");
	int logcondition = false;
	switch (choose)
	{
	case 1:
		system("title Login (-1 back)");
		logcondition = login();
		break;
	case 2:
		system("title Register (-1 back)");
		reg();
		break;
	case 3:
		recover_password();
		break;
	case 4:
		system("title cancel your account");
		logout();
		break;
	case -1:
		exit(0);
		break;
	default:
		cout << "输入错误，请重新输入！" << endl << endl;
		break;
	}
	if (logcondition == true)
	{
		ofstream ofs;
		ofs.open("all_text\\login.log", ios::out);
		ofs << "UID " << it_user->UID << endl;
		ofs << "name " << it_user->name << endl;
		ofs << "logintime " << time(0) << endl;

		//加密签名
		string str;
		MD5 md5;
		str = md5.encode(to_string(it_user->UID));
		str += it_user->name;
		str = md5.encode(str);
		str += md5.encode(it_user->md5_password);
		str = md5.encode(str);

		ofs << "signature " << str << endl;
		ofs.close();

		system("cls");
		cout << "登录成功！" << endl << endl;
	}
	else
	{
		login_menu();
	}
}

void read_user()
{
	ifstream ifs;
	ifs.open("all_text\\AllUser.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开错误，请添加用户数据文件！" << endl;
		ifs.close();
		system("pause");
		system("exit");
	}
	User temp;
	string str;
	while (!ifs.eof())
	{

		ifs >> temp.UID;
		ifs >> temp.name;
		ifs >> temp.md5_password;
		l_user.push_back(temp);
	}
	ifs.close();
}

bool login()
{
	string Name = "", Password = "";
	char c;
	cout << "请输入账号：";
	cin >> Name;
	it_user = find(l_user.begin(), l_user.end(), User(Name));
	if (Name == "-1")
	{
		system("cls");
		return false;
	}
	if (it_user == l_user.end())
	{
		system("cls");
		cout << "账号不存在，请重新输入！" << endl << endl;
		login();
	}
	system("cls");
	cout << "账号：" << Name << endl << endl;
in_pw:
	cout << "请输入密码：";
	while (true)
	{
		c = _getch();
		if (c == '\n' || c == '\r' || c == '\t')
		{
			cout << endl;
			break;
		}
		else if (c == '\b')
		{
			if (Password.empty())
			{
				cout << '\a';
			}
			else
			{
				Password.pop_back();
				cout << "\b \b";
			}
		}
		else
		{
			Password += c;
			cout << '*';
		}
	}
	if (Password == "-1")
	{
		system("cls");
		return false;
	}
	string MD5_Password;
	MD5_Password = md5(Password);
	MD5_Password = md5(MD5_Password + it_user->name);

	if (MD5_Password != it_user->md5_password)
	{
		system("cls");
		cout << "密码错误，请重新输入！" << endl << endl;
		Password = "";
		cout << "账号：" << it_user->name << endl;
		goto in_pw;
	}
	else
	{
		return true;
	}
}
void reg()
{
	ofstream ofs;
	ofs.open("all_text\\AllUser.txt", ios::app);
	if (!ofs.is_open())
	{
		cout << "文件打开错误，用户数据文件不存在！" << endl;
		return;
	}
	//账号注册
	string new_name;
	while (true)
	{
		cout << "账号要求：位数不少于5" << endl;
		cout << "          由数字，字母，特殊字符（半角字符，不包括：@ - ）组成" << endl;
		cout << "          不能是纯数字" << endl << endl;
		cout << "请输入账号：";
		new_name = "";
		cin >> new_name;
		if (new_name == "-1")
		{
			system("cls");
			return;
		}
		else if (new_name.size() < 5)
		{
			system("cls");
			cout << "位数小于5，请重新输入！" << endl << endl;
			continue;
		}
		bool is_number = true;
		bool illegal_char = false;
		for (int i = 0; i < new_name.size(); i++)
		{
			if (new_name[i] == '@' || new_name[i] == '-' || new_name[i] == ' ')
			{
				illegal_char = true;
				break;
			}
			if (!(new_name[i] >= '0' && new_name[i] <= '9'))
			{
				is_number = false;
			}
		}
		if (illegal_char == true)
		{
			system("cls");
			cout << "账号包含非法字符，请重新输入！" << endl << endl;
			continue;
		}
		else if (is_number == true)
		{
			system("cls");
			cout << "账号为纯数字，请重新输入！" << endl << endl;
			continue;
		}
		if (find(l_user.begin(), l_user.end(), User(new_name)) != l_user.end())
		{
			system("cls");
			cout << "账号已存在，请重新输入！" << endl << endl;
			continue;
		}
		break;
	}
	system("cls");
	//密码注册
	string new_password;
	while (true)
	{
		cout << "账号：" << new_name << endl << endl;
		cout << "密码要求：位数不少于8，不大于18" << endl;
		cout << "          在数字，小写字母，大写字母，特殊字符（半角字符，不包括：- ）中至少包含两种" << endl;
		cout << "          不能与账号相同" << endl << endl;
		cout << "请输入密码：";
		new_password = "";
		cin >> new_password;
		if (new_password == "-1")
		{
			system("cls");
			return;
		}
		else if (new_password.size() < 8)
		{
			system("cls");
			cout << "位数小于8，请重新输入！" << endl << endl;
			continue;
		}
		else if (new_password.size() > 18)
		{
			system("cls");
			cout << "位数大于18，请重新输入！" << endl << endl;
			continue;
		}
		bool illegal_char = false;
		for (int i = 0; i < new_password.size(); i++)
		{
			if (new_password[i] == '-' || new_password[i] == ' ')
			{
				illegal_char = true;
				break;
			}
		}
		if (illegal_char == true)
		{
			system("cls");
			cout << "密码包含非法字符，请重新输入！" << endl << endl;
			continue;
		}
		else if (kind_char(new_password) < 2)
		{
			system("cls");
			cout << "密码中的字符种类小于2，请重新输入！" << endl << endl;
			continue;
		}
		if (new_password == new_name)
		{
			system("cls");
			cout << "密码与账号相同，请重新输入！" << endl << endl;
			continue;
		}
		break;
	}
	cout << "注册成功！" << endl << endl;
	string md5_password;
	//密码的MD5加密
	md5_password = md5(new_password);
	md5_password = md5(md5_password + new_name);


	int UID = l_user.back().UID + 1;
	l_user.push_back(User(UID, new_name, md5_password));
	ofs << UID << " " << new_name << " " << md5_password << endl;
	ofs.close();

	//创建用户数据文件
	string command_string = "mkdir all_text\\User\\" + to_string(UID);
	const char* command = data(command_string);
	system(command);

	ofstream of;
	command_string.erase(0, 6);
	of.open(command_string + "\\permanent_record.txt", ios::out);
	of.close();
	of.open(command_string + "\\role_record.txt", ios::out);
	of.close();
	of.open(command_string + "\\weapon_record.txt", ios::out);
	of.close();
	of.open(command_string + "\\resource.txt", ios::out);

	of << "primogems 0" << endl;
	of << "starglitter 0" << endl;
	of << "acquaint_fate 0" << endl;
	of << "intertwined_fate 0" << endl;
	of << "role_amount4 0" << endl;
	of << "role_amount5 0" << endl;
	of << "permanent_amount4 0" << endl;
	of << "permanent_amount5 0" << endl;
	of << "role_guarantee4 0" << endl;
	of << "role_guarantee5 0" << endl;
	of.close();
}
int kind_char(string str)
{
	int n = str.size();
	string kind_str;
	for (int i = 0; i < n; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			kind_str.push_back('n');
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			kind_str.push_back('u');
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			kind_str.push_back('l');
		}
		else
		{
			kind_str.push_back('c');
		}
	}
	vector<char>kind;
	for (int i = 0; i < n; i++)
	{

		if (kind.empty() || find(kind.begin(), kind.end(), kind_str[i]) == kind.end())
		{
			kind.push_back(kind_str[i]);
		}
	}
	return kind.size();
}
void recover_password()
{
	cout << "找回密码功能尚未开发！" << endl;
	cout << "若忘记密码，请联系客服：kefu@zhanglp.cn" << endl << endl;
}
void logout()
{
	cout << "输入错误，请重新输入" << endl << endl;
	return;
	if (!login())
	{
		return;
	}
	cout << "账号已注销！" << endl << endl;
	string command_str;
	command_str = "rmdir /s/q all_text\\User\\" + to_string(it_user->UID);
	system(data(command_str));

	l_user.erase(it_user);
	it_user = l_user.end();
	ofstream ofs;
	ofs.open("all_text\\AllUser.txt", ios::out);
	for (list<User>::iterator it = l_user.begin(); it != l_user.end(); it++)
	{
		ofs << it->UID << " " << it->name << " " << it->md5_password << endl;
	}
	ofs.close();



}