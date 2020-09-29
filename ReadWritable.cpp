#include <iostream>
#include "ReadWritable.h"

namespace sdds
{
	// no-argument constructor sets csv_flag to false
	ReadWritable::ReadWritable()
	{
		csv_flag = false;
	}

	// empty body destructor
	ReadWritable::~ReadWritable() {}

	// returns csv_flag
	bool ReadWritable::isCsv() const
	{
		return csv_flag;
	}

	// sets csv_flag to incoming value
	void ReadWritable::setCsv(bool value)
	{
		csv_flag = value;
	}

	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw)
	{
		rw.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, ReadWritable& rw)
	{
		rw.read(is);
		return is;
	}
}