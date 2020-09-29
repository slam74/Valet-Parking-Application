#ifndef VEHICLE_H_
#define VEHICLE_H_
#include "ReadWritable.h"

namespace sdds
{
	class Vehicle : public ReadWritable
	{
	private:
		char m_licensePlate[9];
		char* m_makeModel;
		int m_parkingSpot;		// parking spot number

	protected:
		void setEmpty();
		bool isEmpty() const;
		const char* getLicensePlate() const;
		const char* getMakeModel() const;
		void setMakeModel(const char* value);

	public:
		Vehicle();
		Vehicle(const char* licensePlate, const char* makeModel);
		Vehicle(const Vehicle&) = delete;
		Vehicle& operator=(const Vehicle&) = delete;
		virtual ~Vehicle();
		int getParkingSpot() const;
		void setParkingSpot(int value);
		bool operator==(const char* licensePlate) const;
		bool operator==(const Vehicle& v) const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};
}

#endif
