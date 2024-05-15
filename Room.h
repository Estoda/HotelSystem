#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h> // atoi() => convert string to int
#include<cstring>  // strcopy() , strcat()
#include<cstdlib> 
#include"Customer.h"
#define ll long long
using namespace std;
class Room
{
private:
	char rNumber[30];//price
	char rFloor[30];
	char rprice[30];
	char rSize[30];
	char buffer[50];
	char id_list[100][10];
	int rec_index_list[100];
	int count;
public:
	char* getRnumber();
	char* getRfloor();
	char* getRprice();
	char* getRsize();
	void input(Customer& c);
	void pack(Customer& c);
	void write()const;
	void creat_two_list();
	int search_id(char key[30]);
	void search();
	void sort();
	void remove();
	void Display(Customer& c);
	void Update(Customer& c);
};
