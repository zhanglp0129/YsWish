
#include<iostream>
#include<ctime>
#include<fstream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<iomanip>


#define NOT_WISH_ROLE INT_MAX

#ifndef _WISH_H_
#define _WISH_H_
using namespace std;
int get_random_number(int, int);
bool menu();
void read_data();
int permanent_item_star();
int win_or_not(double);
void exchange();
void query();
void top_up_primogems();
void wish_menu();
void wish_permanent(int);
void wish_role(int);
void wish_analysis();
void wish_outcome(int, int);
void record();
void data_analysis();
int role_item_star();
void addpool();
int file_line(string);
void user_resource(int);
#endif