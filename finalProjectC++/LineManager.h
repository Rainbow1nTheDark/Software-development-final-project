#ifndef _LINEMANAGER_H
#define _LINEMANAGER_H
#include <vector>
// Name: Alexander Balandin
// Seneca Student ID: 132145194
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <deque>
#include "Workstation.h"
class LineManager
{
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
	Workstation* m_firstStation = nullptr;
public:
	LineManager() { m_cntCustomerOrder = 0; }
	LineManager(std::string fileName, std::vector<Workstation*>& vWorkstation, std::vector<CustomerOrder>& vCustomerOrder);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif