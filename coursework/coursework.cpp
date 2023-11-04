#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
***************
* Created by:  *
* Hristo Sabev *
* *************
*/

/*
This is the base class, that is also an abstract class.
*/
class HotelReservation {
public:
	virtual void setReservation() = 0;
	virtual void displayDetails() = 0;
	virtual double calculateCost() = 0;
};


class Room : public HotelReservation {
private:
	int room_id;
	string room_type;
	double room_cost;
	int status; // 0,1
public:
	// constructor
	Room(int room_id, string room_type, int room_cost, int status, int id, string from, string to, int guests_num) : HotelReservation()
	{
		this->room_id = room_id;
		this->room_type = room_type;
		this->room_cost = room_cost;
		this->status = status;
	}

	void setReservation() override;
	void displayDetails() override;
	double calculateCost() override;
};

void Room::setReservation() {
	cout << "Enter room ID: ";
	cin >> room_id;
	cout << "Enter room type: ";
	cin >> room_type;
	cout << "Enter room cost: ";
	cin >> room_cost;
	cout << "Enter room status: ";
	cin >> status;
};

void Room::displayDetails() {
	cout << "Room ID: " << room_id << endl;
	cout << "Room Type: " << room_type << endl;
	cout << "Room Cost: " << room_cost << endl;
	cout << "Room Status: " << status << endl;
};

double Room::calculateCost() {
	return room_cost;
};

class Customer {
private:
	string name;
	string email;
	string phone;
public:
	Customer(string name, string email, string phone) {
		this->name = name;
		this->email = email;
		this->phone = phone;
	}

	void setCustomer();
	void getCustomer();
};

void Customer::setCustomer() {

	cout << "Enter name: ";
	cin >> name;
	cout << "Enter email: ";
	cin >> email;
	cout << "Enter phone: ";
	cin >> phone;
};

void Customer::getCustomer() {
	cout << "Customer Name: " << name << endl;
	cout << "Customer Email: " << email << endl;
	cout << "Customer Phone: " << phone << endl;
}

class Payment {
private:
	int payment_id;
	string payment_type;
	double amount_paid;
public:
	Payment(int payment_id, string payment_type, double amount_paid) {
		this->payment_id = payment_id;
		this->payment_type = payment_type;
		this->amount_paid = amount_paid;
	}

	void setPayment();
	double getPayment();
};

void Payment::setPayment() {
	cout << "Enter payment_id: ";
	cin >> payment_id;
	cout << "Enter payment_type: ";
	cin >> payment_type;
	cout << "Enter amount_paid: ";
	cin >> amount_paid;

	if (amount_paid < 0) {
		cout << "Invalid amount paid" << endl;
	}
};

double Payment::getPayment() {
	return amount_paid;
};

int main()
{


	return 0;
}
