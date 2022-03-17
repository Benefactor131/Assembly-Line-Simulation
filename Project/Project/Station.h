//MS1
//Student Name: Bair Suimaliev
//Student email: bsuimaliev@myseneca.ca
//Student ID: 159350198
//Date: 11.20.2021
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshopsand assignments.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds {
	class Station {
		int id;
		std::string name;
		std::string desc;
		size_t serial_num;
		size_t num_of_items;
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string &);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H
