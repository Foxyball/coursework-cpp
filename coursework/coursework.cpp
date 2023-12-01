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
			cout << "Nqma nalichni rezervacii\n";
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
			cout << "Nqma nalichni rezervacii za obrabotka\n";
		}
		else {
			totalCost = reservationList[0]->calculateCost();
			reservationList.erase(reservationList.begin());
		}
		return totalCost;
	}

	void saveReservations() {
		fstream fo;
		fo.open("rezervacii.txt", ios::out);
		if (fo.is_open()) {
			for (int i = 0; i < reservationList.size(); i++) {
				fo << reservationList[i]->calculateCost() << "\n";
			}
			fo.close();
		}
		else {
			cout << "Ne moje da se otvori faila\n";
		}


	}
};

void menu() {
	cout << "\tMENU\t\n";
	cout << "1. Add Room Reservation\n";
	cout << "2. Add Event Reservation\n";
	cout << "3. List Reservations\n";
	cout << "4. Process Reservations\n";
	cout << "0. Exit\n";
}

int main() {
	ReservationManager manager;
	int choice;

	while (true) {
		menu();
		cout << "Enter your choice: ";
		cin >> choice;

		// Convert the choice to an integer for comparison
		//int choiceInt = stoi(choice);

		switch (choice) {
		case 1: {
			string guest;
			int room;
			double rate;
			int nights;

			cout << "Guest: ";
			cin.ignore();
			getline(cin, guest);
			cout << "Room Number: ";
			cin >> room;
			cout << "Nightly Rate: ";
			cin >> rate;
			cout << "Number of Nights: ";
			cin >> nights;

			manager.addReservation(new RoomReservation(guest, room, rate, nights));
			break;
		}
		case 2: {
			string guest;
			string event;
			double cost;

			cout << "Guest: ";
			cin.ignore();
			getline(cin, guest);
			cout << "Event: ";
			getline(cin, event);
			cout << "Cost: ";
			cin >> cost;

			manager.addReservation(new EventReservation(guest, event, cost));
			break;
		}
		case 3: {
			manager.listReservations();
			break;
		}
		case 4: {
			double totalCost = manager.processReservations();
			if (totalCost > 0) {
				cout << "Total Cost of Processed Reservations: " << totalCost << "\n";
			}
			break;
		}
		case 0: {
			manager.saveReservations();
			cout << "Vsicki promeni bqxa uspeshno zapisani.\n";
			cout<<"Izhod ot programata.\n";
			return 0;
		}
		default: {
			cout << "Invalid choice. Please enter a valid option.\n";
			break;
		}
		}
	}

}