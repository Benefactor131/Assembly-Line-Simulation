//MS2
//Student Name: Bair Suimaliev
//Student email: bsuimaliev@myseneca.ca
//Student ID: 159350198
//Date: 11.25.2021
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshopsand assignments.
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "CustomerOrder.h"

using namespace std;

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(std::string record) {
		size_t delim = 0;
		bool ok;
		string str = record;
		Utilities utils;
		size_t len = str.size() - 1;

		m_name = utils.extractToken(str, delim, ok);
		m_product = utils.extractToken(str, delim, ok);
		
		m_cntItem = std::count(str.begin() + delim, str.end(), utils.getDelimiter());

		if (str[len] != utils.getDelimiter()) {
			m_cntItem++;
		}

		m_lstItem = new Item *[m_cntItem];

		for_each(m_lstItem, m_lstItem + m_cntItem, [&utils, &str, &delim, &ok](Item* &i) {
			i = new Item(utils.extractToken(str, delim, ok));
		});

		if (m_widthField < utils.getFieldWidth())
		{
			m_widthField = utils.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(CustomerOrder& obj) {
		string e = "Cannot make copies";
		throw e;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& obj)noexcept {
		*this = std::move(obj);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj) noexcept {
		if (this != &obj) {
			for_each(m_lstItem, m_lstItem + m_cntItem, [](Item* i) {
				delete i;
				});
			delete[] m_lstItem;

			m_name = move(obj.m_name);
			m_product = move(obj.m_product);
			m_cntItem = obj.m_cntItem;
			m_lstItem = obj.m_lstItem;

			obj.m_cntItem = 0ul;
			obj.m_lstItem = nullptr;

		}

		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for_each(m_lstItem, m_lstItem + m_cntItem, [](Item* i) {
			delete i;
		});

		delete[] m_lstItem;
	}

	bool CustomerOrder::isFilled() const {
		bool status = all_of(m_lstItem, m_lstItem + m_cntItem, [](const Item* i) {
			return i->m_isFilled;
		});

		return status;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool status = !any_of(m_lstItem, m_lstItem + m_cntItem, [&itemName](const Item* i) {
			return i->m_itemName == itemName && !i->m_isFilled;
		});

		return status;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for_each(m_lstItem, m_lstItem + m_cntItem, [this, &station, &os](Item* i) {
			if (i->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0) {
					i->m_isFilled = true;
					station.updateQuantity();
					i->m_serialNumber = station.getNextSerialNumber();

					os << "    Filled ";
				}
				else {
					os << "    Unable to fill ";
				}

				os << m_name << ", " << m_product << " [" << station.getItemName() << ']' << std::endl;
			}
		});
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for_each(m_lstItem, m_lstItem + m_cntItem, [&os](const Item* i) {
			os << '[' << std::setfill('0') << std::setw(6) << i->m_serialNumber << "] " 
				<< std::setfill(' ') << std::setw(m_widthField) << std::left << i->m_itemName 
				<< " - " << std::right << (i->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		});
	}
}