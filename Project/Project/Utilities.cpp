//MS1
//Student Name: Bair Suimaliev
//Student email: bsuimaliev@myseneca.ca
//Student ID: 159350198
//Date: 11.20.2021
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshopsand assignments.
#include <iostream>
#include <iomanip>
#include "Utilities.h"

using namespace std;

namespace sdds {
	char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		size_t pos = str.find(m_delimiter, next_pos);
		if (pos == next_pos)
		{
			more = false;
			throw "An error occured.";
		}
		else
		{
			more = pos != string::npos;
			string str1 = str.substr(next_pos, pos - next_pos);
			next_pos = pos + 1;
			if (str1.length() > m_widthField)
				setFieldWidth(str1.length());
			return str1;
		}
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}