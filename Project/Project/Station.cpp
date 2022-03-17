//MS1
//Student Name: Bair Suimaliev
//Student email: bsuimaliev@myseneca.ca
//Student ID: 159350198
//Date: 11.20.2021
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshopsand assignments.
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& record) {
		size_t delim = 0;
		bool ok;
		string str = record;
		Utilities utils;

		name = utils.extractToken(str, delim,ok);
		serial_num = stoi(utils.extractToken(str, delim, ok));
		num_of_items = stoi(utils.extractToken(str, delim, ok));

		if (m_widthField < utils.getFieldWidth())
		{
			m_widthField = utils.getFieldWidth();
		}

		desc = utils.extractToken(str, delim, ok);

		id = id_generator++;
		id++;
	}

	const std::string& Station::getItemName() const {
		return name;
	}

	size_t Station::getNextSerialNumber() {
		return serial_num++;
	}

	size_t Station::getQuantity() const {
		return num_of_items;
	}

	void Station::updateQuantity() {
		if (num_of_items == 1)
		{
			num_of_items = 0;
		}
		else
		{
			num_of_items -= 1;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		if (full == false)
		{
			os << "[" << setfill('0') << right << setw(3) << id << "] Item: " << setfill(' ') << setw(m_widthField) << left << getItemName() << " [" << setfill('0') << right << setw(6) << serial_num << "]" << endl;
		}
		else {
			os << "[" << setfill('0') << right << setw(3) << id << "] Item: " << setfill(' ') << setw(m_widthField) << left << getItemName() << " [" << setfill('0') << setw(6) << right << serial_num << "] Quantity: " << setfill(' ') << setw(m_widthField) << left << num_of_items << " Description: " << left << desc << endl;
		}
	}
}