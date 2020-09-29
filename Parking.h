#ifndef PARKING_H_
#define PARKING_H_
#include "Menu.h"
#include "Vehicle.h"

namespace sdds
{
	const int MAX_LOT_SIZE = 100;

	class Parking
	{
	private:
		char* m_dataFile;		// data file name of the application
		Menu m_parkingMenu;
		Menu m_vehicleMenu;
		// MS6
		int m_noOfSpots;		// number of spots, <= MAX_LOT_SIZE
		int m_Vcnt;			// number of parked vehicles, <= m_noOfSpots
		Vehicle* m_parkingSpots[MAX_LOT_SIZE];	// parking spots

		// private member functions
		bool isEmpty() const;
		void setEmpty();
		void parkingStatus();
		void parkVehicle();
		void returnVehicle();
		void listParkedVehicles();
		bool closeParking();
		bool exitParkingApp();
		bool loadDataFile();
		void saveDataFile();

	public:
		Parking(const char* datafile, int noOfSpots);
		Parking(const Parking&) = delete;
		Parking& operator=(const Parking&) = delete;
		~Parking();
		int run();
	};
}

#endif
