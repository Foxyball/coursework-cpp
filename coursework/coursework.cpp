#include <iostream>
#include <string>
using namespace std;

class HotelReservation {
private:
	int id;
	string from;
	string to;
	int guests_num;
	int room_num;
public:
	// constructor
	HotelReservation(int id, string from, string to, int guests_num)
	{
		this->id = id;
		this->from = from;
		this->to = to;
		this->guests_num = guests_num;
	}
	// methods
	void setReservation();
	void getReservation();
};


// implement setReservation
void HotelReservation::setReservation()
{
	cout << "Enter id: ";
	cin >> id;
	cout << "Enter from: ";
	cin >> from;
	cout << "Enter to: ";
	cin >> to;
	cout << "Enter guests_num: ";
	cin >> guests_num;
};

void HotelReservation::getReservation()
{
	cout << "Reservation ID: " << id << endl;
	cout << "Date From: " << from << "to " << to << endl;
	cout << "Guests Numer: " << guests_num << endl;
}

class Room : public HotelReservation {
private:
	int room_id;
	string room_type;
	int room_num;
public:
	// constructor
	Room(int room_id, string room_type, int room_num, int id, string from, string to, int guests_num) : HotelReservation(id, from, to, guests_num)
	{
		this->room_id = room_id;
		this->room_type = room_type;
		this->room_num = room_num;
	}
};

int main()
{

	return 0;
}
