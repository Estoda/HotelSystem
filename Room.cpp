#include"Room.h"
using namespace std;
char* Room::getRnumber()
{
	return rNumber;
}
char* Room::getRfloor()
{
	return rFloor;
}
char* Room::getRprice()
{
	return rprice;
}
char* Room::getRsize()
{
	return rSize;
}
void Room::input(Customer& c)
{
	cout << "Enter room number: " << endl;
	cin >> rNumber;

	cout << "Enter floor: " << endl;
	cin >> rFloor;

	cout << "Enter hour price: " << endl;
	cin >> rprice;

	cout << "Enter room size: " << endl;
	cin >> rSize;
	c.input();
}
void Room::pack(Customer& c)
{
	strcpy_s(buffer, c.getId());
	strcat_s(buffer, "|");
	strcpy_s(buffer, c.getFname());
	strcat_s(buffer, "|");
	strcpy_s(buffer, c.getLname());
	strcat_s(buffer, "|");
	strcpy_s(buffer, rNumber);
	strcat_s(buffer, "|");
	strcat_s(buffer, rFloor);
	strcat_s(buffer, "|");
	strcat_s(buffer, rprice);
	strcat_s(buffer, "|");
	strcat_s(buffer, rSize);
}
void Room::write()const
{
	fstream file;
	file.open("Room_file.txt", ios::app);
	file << buffer << endl;
	file.close();
}
void Room::creat_two_list()
{
	int index = 0;
	count = -1;
	fstream file;
	file.open("Room_file.txt", ios::in);

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
void Room::sort()
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
int Room::search_id(char key[30])
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
void Room::search()
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
		file.open("Room_file.txt", ios::in);
		file.seekp(rec_index, ios::beg);
		file.getline(buffer, '#');
		cout << "Record Found: " << buffer << endl;
	}
	else
		cout << "Record Not Found" << endl;
}
void Room::remove()
{
	cout << " Enter id of the record you want to Delete:" << endl;
	char key[30];
	cin >> key;
	int index = search_id(key);
	if (index != -1)
	{
		fstream file;
		file.open("Room_file.txt", ios::in | ios::out);
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
void Room::Update(Customer& c) {
	cout << "Enter id for the record  you want to update: ";
	char key[30];
	cin >> key;

	int index = search_id(key);
	if (index != -1) {
		int rec_index = rec_index_list[index];

		// Get new data from user
		cout << "Enter new details: room number " << endl;
		cin.ignore(); // Clear input buffer (prevents issues with leftover data)
		cin.getline(rNumber, 30);
		cout << "Enter floor:" << endl;
		cin.getline(rFloor, 30);
		cout << "Enter hour price:" << endl;
		cin.getline(rprice, 30);
		cout << "Enter room size:" << endl;
		cin.getline(rSize, 30);

		// Pack the updated data
		c.Update(*this, key);
		pack(c);

		// Open file in output mode to overwrite existing data
		fstream file;
		file.open("Room_file.txt", ios::out | ios::in);

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
void Room::Display(Customer& c)
{
	cout << "RoomN|1st name|L name|id|floor|hour price|size" << endl;
	fstream file;
	file.open("Room_file.txt", ios::in);
	for (int x = 0; x <= count; x++)
	{
		int rec_index = rec_index_list[x];
		file.seekp(rec_index, ios::beg);
		file.getline(buffer, '#');
		cout << buffer << endl;
	}
	file.close();
	c.Display();
}
