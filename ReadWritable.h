#ifndef READ_WRITABLE_H_
#define READ_WRITABLE_H_
#include <iostream>

namespace sdds
{
	class ReadWritable
	{
	private:
		bool csv_flag;		// comma separated values flag

	public:
		ReadWritable();
		virtual ~ReadWritable();
		bool isCsv() const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream& istr = std::cin) = 0;
		virtual std::ostream& write(std::ostream& ostr = std::cout) const = 0;
	};

	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw);
	std::istream& operator>>(std::istream& is, ReadWritable& rw);
}

#endif