#include <iostream>
#include <cstring>
#include "Car.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
	Car::Car() :Vehicle(), m_carWashFlag(false) {}

	Car::Car(const char* licensePlate, const char* makeModel) : Vehicle(licensePlate, makeModel), m_carWashFlag(false) {}

	std::istream& Car::read(std::istream& istr)
	{
		if (isCsv())
		{
			Vehicle::read(istr);
			istr >> m_carWashFlag;
			istr.ignore(100, '\n');
		}
		else
		{
			cout << "\nCar information entry" << endl;
			Vehicle::read(istr);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			m_carWashFlag = Utils::yes(istr);
		}
		return istr;
	}

	std::ostream& Car::write(std::ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Car Object" << endl;
		}
		else
		{
			(isCsv()) ? ostr << "C," : ostr << "Vehicle type: Car" << endl;

			Vehicle::write(ostr);

			if (isCsv()) {
				ostr << m_carWashFlag << endl;
			}
			else
			{
				(m_carWashFlag) ? ostr << "With Carwash" << endl : ostr << "Without Carwash" << endl;
			}
		}
		return ostr;
	}
}