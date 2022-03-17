//MS3
//Student Name: Bair Suimaliev
//Student email: bsuimaliev@myseneca.ca
//Student ID: 159350198
//Date: 12.04.2021
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
#include <algorithm>
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

	bool LineManager::run(std::ostream& os) {
		static int counter = 0;

		os << "Line Manager Iteration: " << ++counter << endl;
		if (!pending.empty()) {
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}

		for_each(activeLine.begin(), activeLine.end(), [&os](auto* lm) {
			lm->fill(os);
			});

		
		for_each(activeLine.begin(), activeLine.end(), [](auto* lm) {
			(*lm).attemptToMoveOrder();
			});

		return (completed.size() + incomplete.size() == m_cntCustomerOrder) ? true : false;
	}

	void LineManager::linkStations() {
		Workstation* temp = m_firstStation;
		activeLine.clear();

		while (temp) {
			activeLine.push_back(temp);
			temp = temp->getNextStation();
		}
	}

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		Utilities utils;
		string str;
		bool ok = true;
		std::ifstream f(file);

		if (!f) {
			string error = "ERROR: Unable to open [" + file + "] file.";
			throw error;
		}

		while (!f.eof())
		{
			bool more = true;
			size_t delim = 0;
			Workstation* w = nullptr;

			std::getline(f, str);

			if (str.size()) {

				string temp = utils.extractToken(str, delim, more);
				if (temp.size()) {
					auto wstation = std::find_if(stations.begin(), stations.end(), [&temp](const Workstation* ws) {
							return ws->getItemName() == temp; 
						});
					if (wstation != stations.end()) {
						w = *wstation;
						w->setNextStation(nullptr);
					}
				}

				if (more) {
					temp = utils.extractToken(str, delim, more);
					if (temp.size()) {
						auto nextWorkstation = std::find_if(stations.begin(), stations.end(),
							[&temp](const Workstation* ws) {
								return ws->getItemName() == temp; 
							});
						if (nextWorkstation != stations.end()) {
							w->setNextStation(*nextWorkstation);
						}
					}
				}
			}

			if (w) {
				activeLine.push_back(w);

				if (ok) {
					m_firstStation = w;
					ok = false;
				}
			}
		}

		f.close();
		m_cntCustomerOrder = pending.size();
	}

	void LineManager::display(std::ostream& os) const {
		for (auto i : activeLine) {
			i->display(os);
		}
	}

}