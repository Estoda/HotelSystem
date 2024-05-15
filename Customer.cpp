#include "Customer.h"
#include "Room.h"

char* Customer::getId()
{
	return ID;
}
char* Customer::getFname()
{
	return FName;
}
char* Customer::getLname()
{
	return LName;
}
void Customer::changeId(char c[])
{
	for (int i = 0; i < (sizeof(ID) / sizeof(ID[0])); i++)
		if (i < (sizeof(c) / sizeof(c[0])))
			ID[i] = c[i];
		else
		{
			ID[i] = '\0';
			break;
		}
}
void Customer::changeFname(char c[])
{
	for (int i = 0; i < (sizeof(FName) / sizeof(FName[0])); i++)
		if (i < (sizeof(c) / sizeof(c[0])))
			FName[i] = c[i];
		else
		{
			FName[i] = '\0';
			break;
		}
}
void Customer::changeLname(char c[])
{
	for (int i = 0; i < (sizeof(LName) / sizeof(LName[0])); i++)
		if (i < (sizeof(c) / sizeof(c[0])))
			LName[i] = c[i];
		else
		{
			LName[i] = '\0';
			break;
		}
}
void Customer::input()
{
	cout << "Enter the id: " << endl;
	cin >> ID;

	cout << "Enter first name: " << endl;
	cin >> FName;

	cout << "Enter last name: " << endl;
	cin >> LName;

}
void Customer::pack(Room r)
{
	strcat_s(buffer, ID);
	strcat_s(buffer, "|");
	strcat_s(buffer, r.getRnumber());
	strcat_s(buffer, "|");
	strcat_s(buffer, FName);
	strcat_s(buffer, "|");
	strcat_s(buffer, LName);

}
void Customer::write()const
{
	fstream file;
	file.open("Customer_file.txt", ios::app);
	file << buffer << endl;
	file.close();
}
void Customer::creat_two_list()
{
	int index = 0;
	count = -1;
	fstream file;
	file.open("Customer_file.txt", ios::in);

	while (true)
	{
		file.getline(buffer, '#');
		int len = strlen(buffer);
		if (file.eof())
		{
			break;
		}
		if (*buffer == '&')
		{
			index += len + 2;
			continue;
		}
		char* ptr = buffer;
		while (*ptr != '|')
		{
			ptr++;
		}
		*ptr = 0;

		strcpy_s(id_list[++count], buffer);
		rec_index_list[count] = index;
		index += len + 2;
	}
	file.close();
	//for (int x = 0; x <= count; x++)
	//	cout << " id " << id_list[x] << " index " << rec_index_list[x] << endl;
	sort();
	//cout << "_______________" << endl;
	//for (int x = 0; x <= count; x++)
	//	cout << " id " << id_list[x] << " index " << rec_index_list[x] << endl;

}
void Customer::sort()
{
	char temp[30];
	for (int x = 0; x <= count; x++)
		for (int y = x + 1; y <= count; y++)
			if (atoi(id_list[x]) > atoi(id_list[y]))
			{
				strcpy_s(temp, id_list[x]);
				strcpy_s(id_list[x], id_list[y]);
				strcpy_s(id_list[y], temp);

				int temp = rec_index_list[x];
				rec_index_list[x] = rec_index_list[y];
				rec_index_list[y] = temp;
			}
}
int Customer::search_id(char key[30])
{
	int low = 0;
	int high = count;
	int mid = 0;
	int flag = 0;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (atoi(id_list[mid]) == atoi(key))
		{
			flag = 1;
			break;
		}
		if (atoi(key) > atoi(id_list[mid]))
		{
			low = mid + 1;
		}
		if (atoi(key) < atoi(id_list[mid]))
		{
			high = mid - 1;
		}
	}
	if (flag == 1)
		return mid;
	else
		return -1;
}
void Customer::search()
{
	cout << "Enter Key to search: " << endl;
	char key[30];
	cin >> key;
	//sort();
	int index = search_id(key);
	if (index != -1)
	{
		int rec_index = rec_index_list[index];
		fstream file;
		file.open("Customer_file.txt", ios::in);
		file.seekp(rec_index, ios::beg);
		file.getline(buffer, '#');
		cout << "Record Found: " << buffer << endl;
	}
	else
		cout << "Record Not Found" << endl;
}
void Customer::remove()
{
	cout << " Enter id you want to Delete:" << endl;
	char key[30];
	cin >> key;
	int index = search_id(key);
	if (index != -1)
	{
		fstream file;
		file.open("Customer_file.txt", ios::in | ios::out);
		int index_rec = rec_index_list[index];
		file.seekp(index_rec, ios::beg);
		file << '&';
		cout << "Record Deleted" << endl;
		count--;
		file.close();
	}
	else
		cout << "Record Not Found " << endl;
}
void Customer::Update(Room r, char key[]) {

	int index = search_id(key);
	if (index != -1) {
		int rec_index = rec_index_list[index];

		// Get new data from user
		cout << "Enter new details: ID " << endl;
		cin.ignore(); // Clear input buffer (prevents issues with leftover data)
		cin.getline(ID, 30);
		cout << "Enter  first name:" << endl;
		cin.getline(FName, 30);
		cout << "Enter  last name:" << endl;
		cin.getline(LName, 30);

		// Pack the updated data
		pack(r);

		// Open file in output mode to overwrite existing data
		fstream file;
		file.open("Customer_file.txt", ios::out | ios::in);

		// Seek to the record position
		file.seekp(rec_index, ios::beg);

		// Write the updated data
		file << buffer << endl;

		cout << "Record Updated Successfully!" << endl;
		file.close();
	}
	else {
		cout << "Record Not Found!" << endl;
	}
}
void Customer::Display()
{
	cout << "CustID|1st name|L name|number" << endl;
	fstream file;
	file.open("Customer_file.txt", ios::in);
	for (int x = 0; x <= count; x++)
	{
		int rec_index = rec_index_list[x];
		file.seekp(rec_index, ios::beg);
		file.getline(buffer, '#');
		cout << buffer << endl;
	}
	file.close();
}