//MS3
//Student Name: Bair Suimaliev
//Student email: bsuimaliev@myseneca.ca
//Student ID: 159350198
//Date: 12.04.2021
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
#include "Workstation.h"

using namespace std;

namespace sdds {
    Workstation::Workstation(const std::string& str) :Station(str) {}

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        bool ok = false;

        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName())) {
                if (m_pNextStation) {
                    *m_pNextStation += move(m_orders.front());
                }
                else {
                    if (m_orders.front().isFilled()) completed.push_back(std::move(m_orders.front()));
                    else incomplete.push_back(std::move(m_orders.front()));
                }
                m_orders.pop_front();
                ok = true;
            }
            else if (!getQuantity()) {
                if (m_pNextStation) {
                    *m_pNextStation += move(m_orders.front());
                }
                else {
                    incomplete.push_back(move(m_orders.front()));
                }
                m_orders.pop_front();
                ok = true;
            }
        }

        return ok;
    }


    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const {
        os << getItemName();
        if (m_pNextStation) {
            os << " --> " << m_pNextStation->getItemName() << std::endl;
        }
        else
        {
            os << " --> End of Line\n";
        }
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(move(newOrder));
        return *this;
    }

}