#ifndef CAR_H_
#define CAR_H_
#include "Vehicle.h"

namespace sdds
{
	class Car : public Vehicle
	{
	private:
		bool m_carWashFlag;

	public:
		Car();
		Car(const char* licensePlate, const char* makeModel);
		Car(const Car&) = delete;
		Car& operator=(const Car&) = delete;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout) const;
	};
}

#endif
