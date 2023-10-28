#include <iostream>
using namespace std;

class HotelReservation {
private:
	int id;
	string from;
	string to;
	int guests_num;
	int room_num;
public:

	HotelReservation(int id, string from, string to, int guests_num, int room_num)
	{
		this->id = id;
		this->from = from;
		this->to = to;
		this->guests_num = guests_num;
		this->room_num = room_num;
	}
};

int main()
{

}
