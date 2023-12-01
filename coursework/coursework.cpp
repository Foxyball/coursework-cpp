#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Abstract Base Class
class Reservation {
protected:
	string guestName;
public:
	Reservation() {};

	virtual double calculateCost() = 0;
	virtual void displayInfo() = 0;
};

// Derived Classes
class RoomReservation : public Reservation {
private:
	int roomNumber;
	double pricePerNight;
	int numberOfNights;
public:
	RoomReservation(string name, int room, double price, int nights) {
		guestName = name;
		roomNumber = room;
		pricePerNight = price;
		numberOfNights = nights;
	};

	virtual double calculateCost() {
		return pricePerNight * numberOfNights;
	};

	virtual void displayInfo() {
		cout << "Ime: " << guestName << ", Staq: " << roomNumber << "\n";
		cout << "Dni prestoi: " << numberOfNights << ", Suma za plashtane: " << calculateCost() << "\n";
	};
};

class EventReservation : public Reservation {
private:
	string eventName;
	double eventCost;
public:
	EventReservation(string name, string event, double cost) {
		guestName = name;
		eventName = event;
		eventCost = cost;
	};

	virtual double calculateCost() {
		return eventCost;
	};

	virtual void displayInfo() {
		cout << "Ime: " << guestName << ", Vid sabitie: " << eventName << "\n";
		cout << "Suma za plasthane: " << calculateCost() << "\n";
	};
};

class ReservationManager {
private:
	vector<Reservation*> reservationList;
public:
	ReservationManager() {};

	void addReservation(Reservation* res) {
		reservationList.push_back(res);
	}

	void listReservations() {
		if (reservationList.empty()) {
			cout << "No reservations\n";
		}
		else {
			for (int i = 0; i < reservationList.size(); i++) {
				reservationList[i]->displayInfo();
			}
		}
	}

	double processReservations() {
		double totalCost = 0;
		if (reservationList.empty()) {
			cout << "No reservations to process\n";
		}
		else {
			totalCost = reservationList[0]->calculateCost();
			reservationList.erase(reservationList.begin());
		}
		return totalCost;
	}
};

int main() {
	ReservationManager manager;
	string choice = "";

	while (choice != "0") {
		cout << "\tMENU\t\n";
		cout << "1. Add Room Reservation\n";
		cout << "2. Add Event Reservation\n";
		cout << "3. List Reservations\n";
		cout << "4. Process Reservations\n";
		cout << "0. Exit\n";
		cin >> choice;

		cin.ignore('\n', 10);

		if (choice == "1") {
			string guest;
			int room;
			double rate;
			int nights;

			cout << "Guest: ";
			getline(cin, guest);
			cout << "Room Number: ";
			cin >> room;
			cout << "Nightly Rate: ";
			cin >> rate;
			cout << "Number of Nights: ";
			cin >> nights;

			manager.addReservation(new RoomReservation(guest, room, rate, nights));
			cin.ignore('\n', 10);
		}
		else if (choice == "2") {
			string guest;
			string event;
			double cost;

			cout << "Guest: ";
			getline(cin, guest);
			cout << "Event: ";
			getline(cin, event);
			cout << "Cost: ";
			cin >> cost;

			manager.addReservation(new EventReservation(guest, event, cost));
			cin.ignore('\n', 10);
		}
		else if (choice == "3") {
			manager.listReservations();
		}
		else if (choice == "4") {
			double totalCost = manager.processReservations();
			if (totalCost > 0) {
				cout << "Total Cost of Processed Reservations: " << totalCost << "\n";
			}
		}
	}
}
