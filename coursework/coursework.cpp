#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Room {
public:
	Room(int number, double price) {
		this->roomNumber = number;
		this->pricePerNight = price;
	}

	virtual void display() const = 0;
	virtual double calculateCost(int nights) const = 0;

	int roomNumber;
protected:
	double pricePerNight;
};

class StandardRoom : public Room {
public:
	StandardRoom(int number) : Room(number, 100.0) {}

	void display() const override {
		std::cout << "Standard Room #" << roomNumber << " - $" << pricePerNight << " per night\n";
	}

	double calculateCost(int nights) const override {
		return pricePerNight * nights;
	}
};

class DeluxeRoom : public Room {
public:
	DeluxeRoom(int number) : Room(number, 150.0) {}

	void display() const override {
		std::cout << "Deluxe Room #" << roomNumber << " - $" << pricePerNight << " per night\n";
	}

	double calculateCost(int nights) const override {
		return pricePerNight * nights;
	}
};

class Hotel {
public:
	Hotel() {
		rooms.push_back(new StandardRoom(101));
		rooms.push_back(new DeluxeRoom(201));
		// Add more rooms as needed
	}


	void displayRooms() const {
		std::cout << "Available Rooms:\n";
		for (const Room* room : rooms) {
			room->display();
		}
	}

	double reserveRoom(int roomNumber, int nights) {
		for (Room* room : rooms) {
			if (room->roomNumber == roomNumber) {
				double cost = room->calculateCost(nights);
				if (cost != 0.0) {
					// Add reservation details to the file
					std::ofstream reservationFile("reservations.txt", std::ios::app);
					reservationFile << "Room #" << roomNumber << ", Nights: " << nights << ", Cost: $" << cost << "\n";
					reservationFile.close();
					return cost;
				}
			}
		}
		return 0.0; // Room not found
	}

private:
	std::vector<Room*> rooms;
};

void displayMenu() {
	std::cout << "Hotel Reservation System\n";
	std::cout << "1. Display Available Rooms\n";
	std::cout << "2. Reserve a Room\n";
	std::cout << "3. Exit\n";
	std::cout << "Enter your choice: ";
}

int main() {
	Hotel hotel;

	while (true) {
		displayMenu();

		int choice;
		std::cin >> choice;

		double cost;

		switch (choice) {
		case 1:
			hotel.displayRooms();
			break;

		case 2:
			int roomNumber, nights;
			std::cout << "Enter room number: ";
			std::cin >> roomNumber;
			std::cout << "Enter number of nights: ";
			std::cin >> nights;

			// Move initialization outside of switch block
			cost = hotel.reserveRoom(roomNumber, nights);

			if (cost != 0.0) {
				std::cout << "Room reserved successfully. Total cost: $" << cost << "\n";
			}
			else {
				std::cout << "Error: Room not found or invalid input.\n";
			}
			break;

		case 3:
			std::cout << "Exiting program. Thank you!\n";
			return 0;

		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}


	return 0;
}
