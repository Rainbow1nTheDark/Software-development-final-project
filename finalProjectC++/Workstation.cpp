// Name: Alexander Balandin
// Seneca Student ID: 132145194
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <algorithm>
#include "Workstation.h"

Workstation::Workstation(std::string& str) : Station(str)
{
	m_pNextStation = nullptr;

}

void Workstation::runProcess(std::ostream& os)
{
	if (m_orders.empty())
		return;
	m_orders.front().fillItem(*this, os);
}

bool Workstation::moveOrder() 
{
	bool isMoved = false;
	if (!m_orders.empty() && m_orders.front().isItemFilled(getItemName()) && m_pNextStation)
	{
		//move the first order to a pointer of the next xtation
		*m_pNextStation += std::move(m_orders.front());
		m_orders.pop_front();
		isMoved = true;
	}
	return isMoved;

}

void Workstation::setNextStation(Workstation& station)
{
	m_pNextStation = &station;
}

const Workstation* Workstation::getNextStation() const
{
	return m_pNextStation; 
}

bool Workstation::getIfCompleted(CustomerOrder& order)
{
	bool isComplited = false;
	if (!m_orders.empty() && m_orders.back().isOrderFilled())
	{
		order = std::move(m_orders.front());
		m_orders.pop_front();
		isComplited = true;
	}
	return isComplited;
}

void Workstation::display(std::ostream& os) const
{
	os << getItemName() << " --> ";
	if (m_pNextStation != nullptr)
		os  << m_pNextStation->getItemName();
	else
		os << "END OF LINE";
	os << std::endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& co)
{
	m_orders.push_back(std::move(co));
	return *this;
}
