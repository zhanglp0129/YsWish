#include<iostream>
#include<easyx.h>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

#define LOGINSUCCEED true		//登录成功
#define LOGINFAIL false			//登录失败 
#define NAMEMAX 30
#define PASSWORDMAX 20
#define NAMEINPUTTING 1
#define PASSWORDINPUTTING 2
#define NOINPUTING 0

//定义全局变量
string Name = "z", passwd = "1";		//账号和密码
int ic = NOINPUTING;	//ic表示输入状态,input_condition
//函数声明
void init();
void input();
void clearinput();
void input_key();
LPCTSTR StringToLpc(string str);
void output();

//登录功能的主体
void Login()
{

	init();


	input();

	closegraph();
}

void init()
{
	initgraph(800, 450, 0);
	COLORREF background = RGB(240, 240, 240);
	setbkcolor(background);
	cleardevice();
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, _T("请登录"));
	setlinecolor(RGB(50, 50, 50));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("黑体"));
	clearinput();
	outtextxy(250 - 30 * 2 - 10, 150 + 2, _T("账号"));
	outtextxy(250 - 30 * 2 - 10, 200 + 2, _T("密码"));
	fillroundrect(525, 250, 600, 280, 10, 10);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(537, 253, _T("确定"));
}

void clearinput()
{
	setfillcolor(RGB(210, 210, 210));
	fillroundrect(250, 150, 600, 180, 8, 8);
	fillroundrect(250, 200, 600, 230, 8, 8);
}

void input()
{
	int namenum = 0, pwnum = 0;		//表示输入的个数
	int top = 0, left = 0;
	TCHAR tc;
	ExMessage m;
	settextstyle(20, 0, _T("宋体"));
	settextcolor(BLACK);

	while (1)
	{
		getmessage(&m);
		if (m.message == WM_LBUTTONDOWN)
		{
			setfillcolor(RGB(210, 210, 210));
			fillroundrect(250, 150, 600, 180, 8, 8);
			fillroundrect(250, 200, 600, 230, 8, 8);
			if (m.x >= 250 && m.x <= 600 && m.y >= 150 && m.y <= 180)
			{
				//账号输入框
				ic = NAMEINPUTTING;
				setfillcolor(WHITE);
				fillroundrect(250, 150, 600, 180, 8, 8);
				input_key();

			}
			else if (m.x >= 250 && m.x <= 600 && m.y >= 200 && m.y <= 230)
			{
				//密码输入框
				ic = PASSWORDINPUTTING;
				setfillcolor(WHITE);
				fillroundrect(250, 200, 600, 230, 8, 8);


			}
			else if (m.x >= 525 && m.x <= 600 && m.y >= 250 && m.y <= 280)
			{
				//按下确定按钮
				ic = NOINPUTING;


			}
			else
			{
				ic = NOINPUTING;
			}
			output();

		}
		else if (m.message == WM_KEYDOWN)
		{




		}

	}
}
void output()
{
	outtextxy(255, 155, StringToLpc(Name));
	setfillcolor(BLACK);
	for (int i = 0; i < passwd.size(); i++)
	{
		fillcircle(255 + 10 + i * 15, 215, 6);
	}
}
LPCTSTR StringToLpc(string str)
{
	size_t size = str.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;
	return buffer;
}

void input_key()
{
	ExMessage m;
	while (true)
	{
		getmessage(&m);
		if (m.message == WM_LBUTTONDOWN)
		{
			break;
		}
		if (ic == NAMEINPUTTING)
		{
			switch (m.ch)
			{
			case '\n':
			case '\r':			//按下回车



				break;
			case '\t':			//按下制表符Tab



				break;
			case '\b':			//按下删除键



				break;
			default:			//按下其他键，正常输入





				break;
			}
		}
		else if (ic == PASSWORDINPUTTING)
		{

			switch ((char)m.ch)
			{
			case '\n':
			case '\r':			//按下回车



				break;
			case '\t':			//按下制表符Tab
				break;
			case '\b':			//按下删除键



				break;
			default:			//按下其他键，正常输入





				break;
			}
		}
	}
}
void curosr(int ic, int num)
{
	if (ic == NAMEINPUTTING)
	{



	}
	else if (ic == PASSWORDINPUTTING)
	{



	}
	else
	{



	}
}