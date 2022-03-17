//MS3
//Student Name: Bair Suimaliev
//Student email: bsuimaliev@myseneca.ca
//Student ID: 159350198
//Date: 12.04.2021
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"

namespace sdds {
    inline std::deque<CustomerOrder> pending;
    inline std::deque<CustomerOrder> completed;
    inline std::deque<CustomerOrder> incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{ nullptr };
    public:
        Workstation(const std::string& str);
        Workstation(Workstation&) = delete;
        Workstation& operator=(Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}

#endif // !SDDS_WORKSTATION_H
