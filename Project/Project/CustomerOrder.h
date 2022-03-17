//MS2
//Student Name: Bair Suimaliev
//Student email: bsuimaliev@myseneca.ca
//Student ID: 159350198
//Date: 11.25.2021
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshopsand assignments.
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{ 0 };
		Item** m_lstItem{ nullptr };
		static size_t m_widthField;
	public:
		CustomerOrder() {}
		CustomerOrder(std::string record);
		CustomerOrder(CustomerOrder& obj);
		CustomerOrder& operator=(CustomerOrder& obj) = delete;
		CustomerOrder(CustomerOrder&& obj)noexcept;
		CustomerOrder& operator=(CustomerOrder&& obj) noexcept;
		~CustomerOrder();
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif