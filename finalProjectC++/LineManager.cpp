// Name: Alexander Balandin
// Seneca Student ID: 132145194
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"
LineManager::LineManager(std::string fileName, std::vector<Workstation*>& vWorkstation, std::vector<CustomerOrder>& vCustomerOrder)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		throw std::string("Failed to open" + fileName);
	std::string record{}, currentStation{}, nextStation{};
	size_t next_position = 0;
	bool isMore = false;
	Utilities utilities;
	while (file)
	{
		next_position = 0;
		std::getline(file, record);
		currentStation = utilities.extractToken(record, next_position, isMore);
		if (isMore)
			nextStation = utilities.extractToken(record, next_position, isMore);
		else
			nextStation = "";

		for (size_t i = 0; i < vWorkstation.size(); i++)
		{
			if (vWorkstation[i]->getItemName() == currentStation)
			{
				for (size_t j = 0; j < vWorkstation.size(); j++)
				{
					if (vWorkstation[j]->getItemName() == nextStation)
					{
						vWorkstation[i]->setNextStation(*vWorkstation[j]);
						break;
					}
				}
			}
			if (m_firstStation == nullptr)
			{
				for (size_t q = 0; i < vWorkstation.size(); q++)
				{
					if (currentStation == vWorkstation[q]->getItemName())
					{
						m_firstStation = vWorkstation[q];
						break;
					}
						
				}
					
			}
		}
	}
	file.close();
	for (size_t i = 0; i < vCustomerOrder.size(); i++)
		ToBeFilled.push_back(std::move(vCustomerOrder[i]));
	m_cntCustomerOrder = ToBeFilled.size();
	AssemblyLine = vWorkstation;
}

bool LineManager::run(std::ostream& os)
{
	static size_t count = 0;
	std::cout << "Line Manager Iteration: " << ++count << std::endl;
	if (!ToBeFilled.empty())
	{
		*m_firstStation += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}
	for (size_t i = 0; i < AssemblyLine.size(); i++)
		AssemblyLine[i]->runProcess(os);
	for (size_t i = 0; i < AssemblyLine.size(); i++)
	{
		AssemblyLine[i]->moveOrder();
		CustomerOrder co;
		if (AssemblyLine[i]->getIfCompleted(co))
			Completed.push_back(std::move(co));
	}

	return Completed.size() == m_cntCustomerOrder;
}

void LineManager::displayCompletedOrders(std::ostream& os) const
{
	for (auto i = Completed.begin(); i != Completed.end(); i++)
		(*i).display(os);
}

void LineManager::displayStations() const
{
	
	for (auto i = 0u; i < AssemblyLine.size(); i++)
		AssemblyLine[i]->display(std::cout);
}

void LineManager::displayStationsSorted() const
{
	const Workstation* ws = m_firstStation;
	while (ws != nullptr)
	{
		ws->display(std::cout);
		ws = ws->getNextStation();
	}
}
