#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h> // atoi() => convert string to int
#include<cstring>  // strcopy() , strcat()
#include<cstdlib> 
#include"Room.h"
#define ll long long
using namespace std;

class Customer
{
private:
	char ID[30];
	char FName[30];
	char LName[30];
	char buffer[50];
	char id_list[100][10];
	int rec_index_list[100];
	int count;
public:
	char* getId();
	void changeId(char c[]);
	char* getFname();
	void changeFname(char c[]);
	char* getLname();
	void changeLname(char c[]);
	void input();
	void pack(Room* r);
	void write()const;
	void creat_two_list();
	int search_id(char key[30]);
	void search();
	void sort();
	void remove();
	void Display();
	void Update(Room& r, char c[]);
};
