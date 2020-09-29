#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Parking.h"
#include "Utils.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"

using namespace std;

namespace sdds
{
	// custom constructor
	Parking::Parking(const char* datafile, int noOfSpots) :
		m_dataFile(nullptr),
		m_parkingMenu("Parking Menu, select an action:"),
		m_vehicleMenu("Select type of the vehicle:", 1)
	{
		int i;
		for (i = 0;i < MAX_LOT_SIZE;i++)
		{
			m_parkingSpots[i] = nullptr;
		}
		m_Vcnt = 0;

		// if parameter datafile and noOfSpots is valid, allocate memory, copy string, and set noOfSpots
		if (datafile != nullptr && datafile[0] != '\0' && !(noOfSpots < 10 || noOfSpots > MAX_LOT_SIZE))
		{
			int i, size = strlen(datafile);
			m_dataFile = new char[size + 1];
			for (i = 0;i < size;i++)
			{
				m_dataFile[i] = datafile[i];
			}
			m_dataFile[size] = '\0';

			m_noOfSpots = noOfSpots;
		}
		else
		{
			m_noOfSpots=0;
		}

		if (loadDataFile())
		{
			// add to parking menu 5 items
			m_parkingMenu << "Park Vehicle"
				<< "Return Vehicle"
				<< "List Parked Vehicles"
				<< "Close Parking (End of day)"
				<< "Exit Program";
			//add to vehicle menu 3 items
			m_vehicleMenu << "Car"
				<< "Motorcycle"
				<< "Cancel";
		}
		else
		{
			// display error message and set empty state
			cout << "Error in data file" << endl;
			setEmpty();
		}
	}

	// destructor
	Parking::~Parking()
	{
		saveDataFile();
		setEmpty();
		int i;
		for (i = 0;i < m_noOfSpots;i++)
		{
			delete m_parkingSpots[i];
			m_parkingSpots[i] = nullptr;
		}
		
	}
	// returns true if in an empty state, otherwise return false
	bool Parking::isEmpty() const
	{
		return m_dataFile == nullptr;
	}

	// set to an empty state
	void Parking::setEmpty()
	{
		delete[] m_dataFile;
		m_dataFile = nullptr;
	}

	// prints text
	void Parking::parkingStatus()
	{
		cout << "****** Seneca Valet Parking ******" << endl;
		cout << "*****  Available spots: ";
		cout.width(4);
		cout.setf(ios::left);
		cout << m_noOfSpots - m_Vcnt << " *****" << endl;
	}

	// displays vehicle selection menu items and will either exit or create an instance of a Car or Motorcycle based on user selection
	// set CSV to false and read it from console, then find first available null Parking Spot and sets it to the Vehicle pointer
	void Parking::parkVehicle()
	{
		if (m_Vcnt < m_noOfSpots)
		{
			m_vehicleMenu.display();
			int i, done = 0, choice = 0;

			do
			{
				Utils::read(choice, 1, 3, "Invalid selection, try again: ");
			} while (!(choice >= 1 && choice <= 3));

			switch (choice)
			{
			case 1:
				if(m_Vcnt<m_noOfSpots)
				{
					Vehicle* temp = new Car;
					temp->setCsv(false);
					temp->read(cin);

					for (i = 0, done = 0;i < MAX_LOT_SIZE && done == 0;i++)
					{
						if (m_parkingSpots[i] == nullptr)
						{
							m_parkingSpots[i] = temp;
							m_parkingSpots[i]->setParkingSpot(i + 1);
							cout << "\nParking Ticket" << endl;
							m_parkingSpots[i]->write(cout);
							cout << endl;
							m_Vcnt++;
							done = 1;
						}
					}
				}
				break;
			case 2:
				//cout << "Parking Motorcycle" << endl;
				if (m_Vcnt < m_noOfSpots)
				{
					Vehicle* temp = new Motorcycle;
					temp->setCsv(false);
					temp->read(cin);

					for (i = 0, done = 0;i < m_noOfSpots && done == 0;i++)
					{
						if (m_parkingSpots[i] == nullptr)
						{
							m_parkingSpots[i] = temp;
							m_parkingSpots[i]->setParkingSpot(i + 1);
							cout << "\nParking Ticket" << endl;
							m_parkingSpots[i]->write(cout);
							cout << endl;
							m_Vcnt++;
							done = 1;
						}
					}
				}
				break;
			case 3:
				cout << "Parking cancelled" << endl;
				break;
			}
		}
		else
		{
			cout << "Parking is full" << endl;
		}
	}

	// gets licensePlate from user and searches Parked Vehicles for match
	// if found it prints the Vehicle and deletes Vehicle from memory and sets the Parking Spot to nullptr
	void Parking::returnVehicle()
	{
		cout << "Return Vehicle" << endl;
		cout << "Enter Licence Plate Number: ";
		char licensePlate[9];
		Utils::read(licensePlate, 1, 8, "Invalid Licence Plate, try again: ", cin);
		int i;
		for (i = 0;i < m_noOfSpots;i++)
		{
			if (m_parkingSpots[i] != nullptr)
			{
				if (*m_parkingSpots[i] == licensePlate)
				{
					cout << "\nReturning: " << endl;
					m_parkingSpots[i]->setCsv(false);
					m_parkingSpots[i]->write(cout);
					cout << endl;
					delete m_parkingSpots[i];
					m_parkingSpots[i] = nullptr;
					m_Vcnt--;
				}
			}
		}
	}

	// goes through all Parking Spot elements up to noOfSpots and prints all that are not nullptr
	void Parking::listParkedVehicles()
	{
		cout << "*** List of parked vehicles ***" << endl;
		int i;
		for (i = 0;i < m_noOfSpots;i++)
		{
			if (m_parkingSpots[i] != nullptr)
			{
				m_parkingSpots[i]->setCsv(false);
				m_parkingSpots[i]->write(cout);
				cout << "-------------------------------" << endl;
			}
		}
	}

	// if Parking is empty, return true, otherwise prints confirmation message
	// if user chooses no, return false, otherwise prints towing ticket and Vehicle and deletes Vehicle and sets Parking Spot to nullptr for all Vehicles and returns true
	bool Parking::closeParking()
	{
		if (isEmpty())
		{
			cout << "Closing Parking" << endl;
			return true;
		}
		else
		{
			bool confirm = Utils::confirmed("Remove and tow all remaining vehicles from the parking");
			if (confirm)
			{
				cout << "Closing Parking" << endl;
				int i;
				for (i = 0;i < m_noOfSpots;i++)
				{
					if (m_parkingSpots[i] != nullptr)
					{
						cout << "\nTowing request" << endl;
						cout << "*********************" << endl;
						m_parkingSpots[i]->write(cout);

						delete m_parkingSpots[i];
						m_parkingSpots[i] = nullptr;
						m_Vcnt--;
					}
				}
				return true;
			}
			else
			{
				cout << "Aborted!" << endl;
				return false;
			}
		}
	}

	// exit option
	bool Parking::exitParkingApp()
	{
		bool exit = Utils::confirmed("terminate the program");
		if (exit)
		{
			cout << "Exiting program!" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}

	// if not empty state print text and return true, otherwise return false
	bool Parking::loadDataFile()
	{
		bool state;
		if (!isEmpty())
		{
			// open m_dataFile
			ifstream file(m_dataFile);
			// if opening file is unsuccessful or Parking was in an empty state, return true upon exit
			if (!file)
			{
				state = true;
			}
			else
			{
				while (file.good() && m_Vcnt < m_noOfSpots)
				{
					Vehicle* temp;
					char type = file.get();
					file.ignore();

					if (type == 'M')
					{
						temp = new Motorcycle;
						temp->setCsv(true);
						temp->read(file);
						if (!file.bad())
						{
							int spotNo = temp->getParkingSpot();
							m_parkingSpots[spotNo - 1] = temp;
							m_Vcnt++;
						}
						else
						{
							delete temp;
						}
					}

					else if (type == 'C')
					{
						temp = new Car;
						temp->setCsv(true);
						temp->read(file);
						if (!file.bad())
						{
							int spotNo = temp->getParkingSpot();
							m_parkingSpots[spotNo - 1] = temp;
							m_Vcnt++;
						}
						else
						{
							delete temp;
						}
					}
				}
				state = true;
			}
			file.clear();
			file.close();
		}
		else
		{
			state = false;
		}
		return state;
	}

	// open m_dataFile using an instance of ofstream class.
	// if successfully opened, then go through all the elements of the Parking Spots that are not null and save the Vehicles in the data file
	void Parking::saveDataFile()
	{
		ofstream file(m_dataFile);
		file.clear();
		if (file)
		{
			int i;
			for (i = 0;i < m_noOfSpots;i++)
			{
				if (m_parkingSpots[i] != nullptr)
				{
					m_parkingSpots[i]->setCsv(true);
					// save the Vehicle in the data file using the ofstream object in Comma Separated mode
					m_parkingSpots[i]->write(file);
				}
			}
		}
		
		file.close();
	}

	// runs the whole Parking Application and 
	// returns 1 if Parking is in empty state, otherwise returns 0
	int Parking::run()
	{
		bool done = false;
		int choice = 0;
		while (!isEmpty() && !done)
		{
			parkingStatus();
			m_parkingMenu.display();
			Utils::read(choice, 1, 5, "Invalid selection, try again: ");
			switch (choice)
			{
			case 1:
				parkVehicle();
				break;
			case 2:
				returnVehicle();
				break;
			case 3:
				listParkedVehicles();
				break;
			case 4:
				done = closeParking();
				break;
			case 5:
				done = exitParkingApp();
				break;
			default:
				break;
			}
		}

		return (isEmpty()) ? 1 : 0;
	}
}