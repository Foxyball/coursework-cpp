#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

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

	string getGuestName() {
		return guestName;
	}

	string getCheckInDate() {
		return checkInDate;
	}

	string getCheckOutDate() {
		return checkOutDate;
	}

};

// Derived Classes
// StandardReservation
class StandardReservation : public Reservation {
private:
	int roomNumber;
	double pricePerNight;
	int numberOfNights;
public:
	StandardReservation(string name, string checkIn, string checkOut, int roomID, int nights) {
		guestName = name;
		checkInDate = checkIn;
		checkOutDate = checkOut;
		roomNumber = roomID;
		pricePerNight = 50;
		numberOfNights = nights;
	};

	virtual double calculateCost() {
		// 2% discount for more than 5 nights
		if (numberOfNights > 5) {
			return pricePerNight * numberOfNights * 0.02;
		}
		else {
			return pricePerNight * numberOfNights;
		}
	};

	virtual void displayInfo() {
		cout << "Name: " << guestName << ", Room number: " << roomNumber << "\n";
		cout << "Check-in date: " << checkInDate << ", Check-out date: " << checkOutDate << "\n";
		cout << "How many days: " << numberOfNights << ", Total Price: " << calculateCost() << " lv." << "\n";
	};
};
// VipReservation
class VipReservation : public Reservation {
private:
	int roomNumber;
	double vipCost;
	double drinkDiscount;
	int numberofNights;
public:
	VipReservation(string name, string checkIn, string checkOut, int roomID, int nights) {
		guestName = name;
		checkInDate = checkIn;
		checkOutDate = checkOut;
		roomNumber = roomID;
		vipCost = 80;
		drinkDiscount = 0.02;
		numberofNights = nights;
	};

	virtual double calculateCost() {
		return vipCost * numberofNights * (1 - drinkDiscount);
	};

	virtual void displayInfo() {
		cout << "Name: " << guestName << ", Room number: " << roomNumber << "\n";
		cout << "Check-in date: " << checkInDate << ", Check-out date: " << checkOutDate << "\n";
		cout << "Suma za plasthane: " << calculateCost() << " lv." << "\n";
	};
};
// Derived Classes
// BusinessReservation
class BusinessReservation :public Reservation {
private:
	int roomNumber;
	double pricePerNight = 100;
	double discount = 0.1;
	int numberOfNights;
	string bulstat;


public:
	BusinessReservation(string companyName, string checkIn, string checkOut, int roomID, int nights, string bul) {
		guestName = companyName;
		checkInDate = checkIn;
		checkOutDate = checkOut;
		roomNumber = roomID;
		numberOfNights = nights;
		setBulstat(bul);
	};

	bool validateBulstat(string bulstat) {
		if (bulstat.length() != 9) {
			return false;
		}
		for (int i = 0; i < bulstat.length(); i++) {
			if (!isdigit(bulstat[i])) {
				return false;
			}
		}
		return true;
	}

	void setBulstat(string bulstat) {
		while (!validateBulstat(bulstat)) {
			cout << "You have entered an invalid bulstat. It must be 9 digits.(Try again).\n";
			cin >> bulstat;
		}
		this->bulstat = bulstat;
	}

	virtual double calculateCost() {
		return pricePerNight * numberOfNights * (1 - discount);
	};

	virtual void displayInfo() {
		cout << "Firm Name: " << guestName << ", Room number: " << roomNumber << "\n";
		cout << "Bulstat: " << bulstat << "\n";
		cout << "Check-in date: " << checkInDate << ", Check-out date: " << checkOutDate << "\n";
		cout << "How many days: " << numberOfNights << ", Total Price: " << calculateCost() << " lv." << "\n";
	}
};
// ReservationManager (The class that manages the reservations)
class ReservationManager {
private:
	vector<Reservation*> reservationList;
public:
	ReservationManager() {};

	void saveToFile(Reservation* res) {
		fstream fo;
		fo.open("rezervacii.txt", ios::out | ios::app);
		try {
			if (!fo.is_open()) {
				throw exception("The storage file could not be opened. Please try again later.");
			}
		}
		catch (exception e) {
			cout << "Error: " << e.what() << "\n";
			return;
		}
		fo << "Name: " << res->getGuestName() << "\n";
		fo << "Check-in date: " << res->getCheckInDate() << "\n";
		fo << "Check-out date: " << res->getCheckOutDate() << "\n";
		fo << "Total Price: " << res->calculateCost() << " lv." << "\n";
		fo << "\n";
		fo.close();
	}

	void addReservation(Reservation* res) {
		reservationList.push_back(res);
		saveToFile(res);
	}

	void listReservations() {
		if (reservationList.empty()) {
			cout << "No reservations available for listing.\n";
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
			cout << "No reservations available for processing.\n";
		}
		else {
			totalCost = reservationList[0]->calculateCost();
			reservationList.erase(reservationList.begin()); // Remove the first element
		}
		return totalCost;
	}
};



// Menu
void menu() {
	cout << "\tMENU\t\n";
	cout << "=============================\n";
	cout << "1. Add reservation\n";
	cout << "2. Add VIP reservation\n";
	cout << "3. Add business reservation\n";
	cout << "4. List reservations\n";
	cout << "5. Process and Save\n";
	cout << "0. Exit\n";
	cout << "=============================\n";
}

int main() {
	ReservationManager manager;
	int choice;

	while (true) {
		menu();
		cout << "Choose an option(number): ";
		cin >> choice;

		switch (choice) {
		case 1: {
			string guest;
			string checkIn;
			string checkOut;
			int room;
			int nights;

			cout << "Name(First and Last): ";
			cin.ignore();
			getline(cin, guest);
			cout << "Room number(number): ";
			cin >> room;
			cout << "How many days(number): ";
			cin >> nights;
			cout << "Check-in date(d.mm.YYYY): ";
			cin >> checkIn;
			cout << "Check-out date(d.mm.YYYY): ";
			cin >> checkOut;

			manager.addReservation(new StandardReservation(guest, checkIn, checkOut, room, nights));
			break;
		}
		case 2: {
			string vipGuest;
			string checkIn;
			string checkOut;
			int room;
			int nights;

			cout << "Name(First and Last): ";
			cin.ignore();
			getline(cin, vipGuest);
			cout << "Room number(number): ";
			cin >> room;
			cout << "How many days(number): ";
			cin >> nights;
			cout << "Check-in date(d.mm.YYYY): ";
			cin >> checkIn;
			cout << "Check-out date(d.mm.YYYY): ";
			cin >> checkOut;

			manager.addReservation(new VipReservation(vipGuest, checkIn, checkOut, room, nights));
			break;
		}
		case 3: {
			string companyName;
			string checkIn;
			string checkOut;
			int room;
			int nights;
			string bulstat;

			cout << "Firm Name: ";
			cin.ignore();
			getline(cin, companyName);
			cout << "Room number(number): ";
			cin >> room;
			cout << "How many days(number): ";
			cin >> nights;
			cout << "Check-in date(d.mm.YYYY): ";
			cin >> checkIn;
			cout << "Check-out date(d.mm.YYYY): ";
			cin >> checkOut;
			cout << "Bulstat(9 digits): ";
			cin >> bulstat;

			manager.addReservation(new BusinessReservation(companyName, checkIn, checkOut, room, nights, bulstat));
			break;
		}
		case 4: {
			manager.listReservations();
			break;
		}
		case 5: {
			double totalCost = manager.processReservations();
			if (totalCost > 0) {
				cout << "Total cost: " << totalCost << " lv.\n";
			}
			break;
		}
		case 0: {
			cout << "Everything is saved. Goodbye!\n";
			return 0;
		}
		default: {
			cout << "Invalid option. Please try again or contact the administrators.\n";
			break;
		}
		}
	}
}