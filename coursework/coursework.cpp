#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/*
	VipReservation - X
	BusinessReservation - X
	exception handling - X

	Problems:
	Нямаме нужда от numberOfNights сега, заради датите.
	Не сме валидирали датите.

	Fixes:
	Имаме достатъчно информация, която се записва във файла [ saveToFile(). ] метода.
*/

// Abstract Base Class
class Reservation {
protected:
	string guestName;
	string checkInDate;
	string checkOutDate;

public:
	Reservation() {};

	virtual double calculateCost() = 0;
	virtual void displayInfo() = 0;

	// Get the guest name
	string getGuestName() {
		return guestName;
	}

	// Get the check in date
	string getCheckInDate() {
		return checkInDate;
	}

	// Get the check out date
	string getCheckOutDate() {
		return checkOutDate;
	}

};

// Derived Classes
class StandardRoomReservation : public Reservation {
private:
	int roomNumber;
	double pricePerNight;
	int numberOfNights;
public:
	StandardRoomReservation(string name, string checkIn, string checkOut, int room, int nights) {
		guestName = name;
		checkInDate = checkIn;
		checkOutDate = checkOut;
		roomNumber = room;
		pricePerNight = 50; // 50lv za noshtuvka
		numberOfNights = nights;
	};

	virtual double calculateCost() {
		return pricePerNight * numberOfNights;
	};

	virtual void displayInfo() {
		cout << "Ime: " << guestName << ", Staq: " << roomNumber << "\n";
		cout << "Data na nastanqvane: " << checkInDate << ", Data na napuskane: " << checkOutDate << "\n";
		cout << "Dni prestoi: " << numberOfNights << ", Suma za plashtane: " << calculateCost() << "\n";
	};
};
// Derived Classes
class EventReservation : public Reservation { // tozi klas trqbva da go smenim s VipREservation + BusinessReservation
private:
	string eventName;
	double eventCost;
public:
	EventReservation(string name, string checkIn, string checkOut, string event) {
		guestName = name;
		checkInDate = checkIn;
		checkOutDate = checkOut;
		eventName = event;
		eventCost = 80; // 80lv za sabitie
	};

	virtual double calculateCost() {
		return eventCost;
	};

	virtual void displayInfo() {
		cout << "Ime: " << guestName << ", Vid sabitie: " << eventName << "\n";
		cout << "Data na nastanqvane: " << checkInDate << ", Data na napuskane: " << checkOutDate << "\n";
		cout << "Suma za plasthane: " << calculateCost() << "\n";
	};
};
// Vector Class
class ReservationManager {
private:
	vector<Reservation*> reservationList;
public:
	ReservationManager() {};

	void saveToFile(Reservation* res) {
		fstream fo;
		fo.open("rezervacii.txt", ios::out | ios::app);
		if (!fo.is_open()) {
			cout << "Ne moje da se otvori faila\n";
			return;
		}
		fo << "Ime: " << res->getGuestName() << "\n";
		fo << "Data na nastanqvane: " << res->getCheckInDate() << "\n";
		fo << "Data na napuskane: " << res->getCheckOutDate() << "\n";
		fo << "Suma za plashtane: " << res->calculateCost() << "\n";
		fo << "\n";
		fo.close();
	}

	void addReservation(Reservation* res) {
		reservationList.push_back(res);
		saveToFile(res);
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
	cout << "1. Add reservation\n";
	cout << "2. Dobavi sabitie\n";
	cout << "3. List reservations\n";
	cout << "4. Process\n";
	cout << "0. Exit\n";
	cout << "=============================\n";
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
			string checkIn;
			string checkOut;
			int room;
			int nights;

			cout << "Ime: ";
			cin.ignore();
			getline(cin, guest);
			cout << "Staq: ";
			cin >> room;
			cout << "Dni prestoi: ";
			cin >> nights;
			cout << "Check-In: ";
			cin >> checkIn;
			cout << "Check-Out: ";
			cin >> checkOut;

			manager.addReservation(new StandardRoomReservation(guest, checkIn, checkOut, room, nights));
			break;
		}
		case 2: {
			string guest;
			string checkIn;
			string checkOut;
			string event;

			cout << "Ime: ";
			cin.ignore();
			getline(cin, guest);
			cout << "Vid sabitie: ";
			getline(cin, event);
			cout << "Check-In: ";
			cin >> checkIn;
			cout << "Check-Out: ";
			cin >> checkOut;

			manager.addReservation(new EventReservation(guest, checkIn, checkOut, event));
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
			break;
		}
		case 0: {
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