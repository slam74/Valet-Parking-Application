#include <iostream>
#include "Motorcycle.h"
#include "Vehicle.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
	Motorcycle::Motorcycle() :Vehicle(), m_hasSideCarFlag(false) {}

	Motorcycle::Motorcycle(const char* licensePlate, const char* makeModel) : Vehicle(licensePlate, makeModel), m_hasSideCarFlag(false) {}

	std::istream& Motorcycle::read(std::istream& istr)
	{
		if (isCsv())
		{
			Vehicle::read(istr);
			istr >> m_hasSideCarFlag;
			istr.ignore(100, '\n');
		}
		else
		{
			cout << "\nMotorcycle information entry" << endl;
			Vehicle::read(istr);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			m_hasSideCarFlag = Utils::yes(istr);
		}
		return istr;
	}

	std::ostream& Motorcycle::write(std::ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Motorcycle Object" << endl;
		}
		else
		{
			(isCsv()) ? ostr << "M," : ostr << "Vehicle type: Motorcycle" << endl;
			
			Vehicle::write(ostr);
			
			if (isCsv())
			{
				ostr << m_hasSideCarFlag << endl;
			}
			else
			{
				if (m_hasSideCarFlag)
				{
					ostr << "With Sidecar" << endl;
				}
			}
		}
		return ostr;
	}
}