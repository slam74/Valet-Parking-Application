#include <iostream>
#include <cstring>
#include "Vehicle.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
	void Vehicle::setEmpty()
	{
		if (m_makeModel != nullptr)
		{
			delete[] m_makeModel;
		}
		m_licensePlate[0] = '\0';
		m_makeModel = nullptr;
		m_parkingSpot = 0;
	}

	bool Vehicle::isEmpty() const
	{
		return m_makeModel == nullptr;
	}

	const char* Vehicle::getLicensePlate() const
	{
		return m_licensePlate;
	}

	const char* Vehicle::getMakeModel() const
	{
		return m_makeModel;
	}

	void Vehicle::setMakeModel(const char* value)
	{
		if (value != nullptr && value[0] != '\0')
		{
			delete[] m_makeModel;
			m_makeModel = new char[strlen(value) + 1];
			//strcpy(m_makeModel, value);
			strcpy_s(m_makeModel, strlen(value) + 1, value);
		}
		else
		{
			setEmpty();
		}
	}

	Vehicle::Vehicle() :ReadWritable(), m_licensePlate{}, m_makeModel(nullptr), m_parkingSpot(0)
	{
		setEmpty();
	}

	Vehicle::Vehicle(const char* licensePlate, const char* makeModel) : ReadWritable(), m_licensePlate{}, m_makeModel(nullptr), m_parkingSpot(0)
	{
		if (licensePlate != nullptr && licensePlate[0] != '\0' && strlen(licensePlate) <= 8 && makeModel != nullptr && makeModel[0] != '\0' && strlen(makeModel) > 1)
		{
			//strcpy(m_licensePlate, licensePlate);
			strcpy_s(m_licensePlate, 9, licensePlate);
			Utils::toUpper(m_licensePlate);
			setMakeModel(makeModel);
		}
		else
		{
			setEmpty();
		}
	}

	Vehicle::~Vehicle()
	{
		delete[] m_makeModel;
	}

	int Vehicle::getParkingSpot() const
	{
		return m_parkingSpot;
	}

	void Vehicle::setParkingSpot(int value)
	{
		if (value < 0)
		{
			setEmpty();
		}
		else
		{
			m_parkingSpot = value;
		}
	}

	// compares m_licensePlate with licensePlate and returns true if identical, otherwise returns false
	bool Vehicle::operator==(const char* licensePlate) const
	{
		if (!isEmpty() && licensePlate != nullptr && licensePlate[0] != '\0')
		{
			char temp[9];
			//strcpy(temp, licensePlate);
			strcpy_s(temp, 9, licensePlate);
			Utils::toUpper(temp);
			if (strcmp(m_licensePlate, temp) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	// compares two Vehicles and returns true if they have the same license plate, otherwise return false
	bool Vehicle::operator==(const Vehicle& v) const
	{
		return operator==(v.m_licensePlate);
	}

	std::istream& Vehicle::read(std::istream& istr)
	{
		int parkingSpot;
		char makeModel[61];

		// check if the Vehicle is set to comma separated mode
		if (isCsv())
		{
			istr >> parkingSpot;
			istr.ignore(1, ',');
			istr.getline(m_licensePlate, 9, ',');
			Utils::toUpper(m_licensePlate);
			istr.getline(makeModel, 60, ',');

			setParkingSpot(parkingSpot);
			setMakeModel(makeModel);
		}
		else
		{
			cout << "Enter Licence Plate Number: ";
			Utils::read(m_licensePlate, 1, 8, "Invalid Licence Plate, try again: ", istr);
			cout << "Enter Make and Model: ";
			Utils::read(makeModel, 2, 60, "Invalid Make and model, try again: ", istr);
			if (istr)
			{
				setMakeModel(makeModel);
				Utils::toUpper(m_licensePlate);
			}
			else
			{
				setEmpty();
			}
		}

		return istr;
	}

	std::ostream& Vehicle::write(std::ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Vehicle Object" << endl;
		}
		else
		{
			// check if Vehicle is in comma separated mode
			if (isCsv())
			{
				ostr << m_parkingSpot << "," << m_licensePlate << "," << m_makeModel << ",";
			}
			else
			{
				ostr << "Parking Spot Number: ";
				(m_parkingSpot == 0) ? ostr << "N/A" << endl : ostr << m_parkingSpot << endl;
				ostr << "Licence Plate: " << m_licensePlate << endl;
				ostr << "Make and Model: " << m_makeModel << endl;
			}
		}
		return ostr;
	}

}