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

	// Get the guest name
	string getGuestName() {
		return guestName;
	}
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
// Derived Classes
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
// Vector Class
class ReservationManager {
private:
	vector<Reservation*> reservationList;
public:
	ReservationManager() {};

	void addReservation(Reservation* res) {
		reservationList.push_back(res);

		fstream fo;
		fo.open("rezervacii.txt", ios::out | ios::app);
		if (!fo.is_open()) {
			cout << "Ne moje da se otvori faila\n";
			return;
		}
		fo << "Ime: " << res->getGuestName() << "\n";
		fo << "Suma za plashtane: " << res->calculateCost() << "\n";
		fo << "Info: "; res->displayInfo();
		fo << "\n";
		fo.close();
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
};



// Menu
void menu() {
	cout << "\tMENU\t\n";
	cout << "=============================\n";
	cout << "1. Dobavi rezervaciq\n";
	cout << "2. Dobavi sabitie\n";
	cout << "3. Pokaji rezervacii\n";
	cout << "4. Obrabotka na rezervacii\n";
	cout << "=============================\n";
	cout << "0. Izxod\n";
}

int main() {
	ReservationManager manager;
	int choice;

	while (true) {
		menu();
		cout << "Izberete: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			string guest;
			int room;
			double price;
			int nights;

			cout << "Ime: ";
			cin.ignore();
			getline(cin, guest);
			cout << "Staq: ";
			cin >> room;
			cout << "Suma za plashtane: ";
			cin >> price;
			cout << "Dni prestoi: ";
			cin >> nights;

			manager.addReservation(new RoomReservation(guest, room, price, nights));
			break;
		}
		case 2: {
			string guest;
			string event;
			double cost;

			cout << "Ime: ";
			cin.ignore();
			getline(cin, guest);
			cout << "Vid sabitie: ";
			getline(cin, event);
			cout << "Suma za plashtane: ";
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
				cout << "Obshta daljima suma: " << totalCost << "\n";
			}
			//manager.storeReservations();
			break;
		}
		case 0: {
			//manager.storeReservations();
			cout << "Vsicki promeni bqxa uspeshno zapisani.\n";
			cout << "Izhod ot programata.\n";
			return 0;
		}
		default: {
			cout << "Nevaliden izbor. Molq, opitaite otnovo\n";
			break;
		}
		}
	}



}