#include<iostream>
#include<string>
#include<fstream>
#include"Customer.h"
#include"Room.h"
using namespace std;

void choices()
{
	cout << "\t\t*******************************************" << endl;
	cout << "\t\t* Enter 1 to insert    Enter 2 to display *" << endl;
	cout << "\t\t* Enter 3 to search    Enter 4 to remve   *" << endl;
	cout << "\t\t* Enter 5 to update    Enter -1 to end    *" << endl;
	cout << "\t\t*******************************************" << endl << endl;
}
int main()
{
	Room r;
	Customer c;

	int choice = 0;
	while (choice != -1)
	{
		if (choice == -1 || choice == 1 || choice == 3 || choice == 4 || choice == 5)
			system("cls");
		choices();
		cout << "Enter Your choice:" << endl;
		cin >> choice;
		if (choice != -1 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)
		{
			system("cls");
			cout << "There is no choice like that !!" << endl;
			continue;
		}
		r.creat_two_list();
		switch (choice)
		{
		case 1:

			r.input(c);
			r.pack(c);
			c.pack(r);
			r.write();
			c.write();
			break;
		case 2:
			system("cls");
			r.Display(c);
			break;
		case 3:
			r.search();
			c.search();
			break;
		case 4:
			r.remove();
			c.remove();
			break;
		case 5:
			r.Display(c);
			r.Update(c);
			break;
		}
	}
	return 0;
	return 0;
}