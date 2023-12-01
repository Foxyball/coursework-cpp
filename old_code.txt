#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// cannot create an instance of an abstract class!!!
class Room {
public:
	int roomNumber;

	Room(int number, double price) {
		this->roomNumber = number;
		this->pricePerNight = price;
	}

	virtual void display() const = 0;
	virtual double calculateCost(int nights) const = 0;

protected:
	double pricePerNight;
};

class StandardRoom : public Room {
public:
	StandardRoom(int number) : Room(number,100.0) {
		this->roomNumber = number;
		this->pricePerNight = 100.0;
	}

	void display() const override {
		cout << "Standard Room #" << roomNumber << " - $" << pricePerNight << " per night\n";
	}

	double calculateCost(int nights) const override {
		return pricePerNight * nights;
	}
};

class DeluxeRoom : public Room {
public:
	DeluxeRoom(int number) : Room(number, 150.0) {}

	void display() const override {
		cout << "Deluxe Room #" << roomNumber << " - $" << pricePerNight << " per night\n";
	}

	double calculateCost(int nights) const override {
		return pricePerNight * nights;
	}
};

class Hotel {
public:
	Hotel() {
		rooms.push_back(new StandardRoom(101));
		rooms.push_back(new StandardRoom(102));
		rooms.push_back(new DeluxeRoom(201));
		// Add more rooms as needed
	}

	void displayRooms() const {
		cout << "Available Rooms:\n";
		for (const Room* room : rooms) {
			room->display();
		}
	}

	double reserveRoom(int roomNumber, int nights) {
		for (Room* room : rooms) {
			if (room->roomNumber == roomNumber) {
				double cost = room->calculateCost(nights);

				if (cost != 0.0) {
					string customerName, customerPhone;
					cout << "Enter customer name: ";
					cin.ignore();
					getline(cin, customerName);

					cout << "Enter customer phone number: ";
					cin >> customerPhone;

					// Add reservation details to the file
					fstream reservationFile;
					reservationFile.open("reservations.txt", ios::app);
					if (!reservationFile.is_open()) {
						cout << "Error: Unable to open file.\n";
						return 0;
					}
					reservationFile << "Room #" << roomNumber << ", Customer: " << customerName
						<< ", Phone: " << customerPhone << ", Nights: " << nights << ", Cost: $" << cost
						<< "\n";
					reservationFile.close();

					return cost;
				}
			}
		}

		return 0.0; // Room not found
	}

	//void clearReservations() {
	//	
	//	fstream fc;
	//	fc.open("reservations.txt", ios::trunc);				// TO DO
	//	if (!fc.is_open()) {
	//		cout << "Error: Unable to open file.\n";
	//		return;
	//	}
	//	fc.close();


	//}

private:
	vector<Room*> rooms;
};

void displayMenu() {
	cout << "\nMenu:\n";
	cout << "1. Display Avaliable Rooms.\n";
	cout << "2. Make a Reservation.\n";
	cout << "3. Clear Reservations.\n";
	cout << "-------------------------\n";
	cout << "4. Exit\n";
	cout << "Enter your choice: ";
}

int main() {
	Hotel hotel;

	while (true) {
		displayMenu();

		int choice;
		cin >> choice;

		double cost;

		switch (choice) {
		case 1:
			hotel.displayRooms();
			break;

		case 2:
			int roomNumber, nights;
			cout << "Enter room number: ";
			cin >> roomNumber;
			cout << "Enter number of nights: ";
			cin >> nights;

			cost = hotel.reserveRoom(roomNumber, nights);

			if (cost != 0.0) {
				cout << "Room reserved successfully. Total cost: $" << cost << "\n";
			}
			else {
				cout << "Error: Room not found or invalid input.\n";
			}
			break;

		case 3:
			cout<<"Clearing reservations...\n";
			break;

		case 4:
			cout << "Exiting program. Thank you!\n";
			return 0;

		default:
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}
