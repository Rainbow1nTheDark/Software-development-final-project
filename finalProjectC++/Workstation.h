// Name: Alexander Balandin
// Seneca Student ID: 132145194s
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef _WORKSTATION_H
#define _WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
class Workstation : public Station
{
	std::deque<CustomerOrder>m_orders;
	Workstation* m_pNextStation;
public:
	Workstation() : Station() {}
	Workstation( std::string& str);
	void runProcess(std::ostream&);
	bool moveOrder();
	void setNextStation(Workstation& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream&) const;
	Workstation& operator+=(CustomerOrder&&);
	Workstation(const Workstation& ws) = delete;
	Workstation(const Workstation&& ws) = delete;
	Workstation& operator=(Workstation& ws) = delete;
	Workstation& operator=(Workstation&& ws) = delete;
};

#endif