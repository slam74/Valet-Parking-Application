#ifndef MOTORCYCLE_H_
#define MOTORCYCLE_H_
#include "Vehicle.h"

namespace sdds
{
	class Motorcycle : public Vehicle
	{
	private:
		bool m_hasSideCarFlag;

	public:
		Motorcycle();
		Motorcycle(const char* licensePlate, const char* makeModel);
		Motorcycle(const Motorcycle&) = delete;
		Motorcycle& operator=(const Motorcycle&) = delete;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout) const;
	};
}

#endif
