// Name: Alexander Balandin
// Seneca Student ID: 132145194
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iomanip>
#include "Utilities.h"
#include "CustomerOrder.h"
size_t CustomerOrder::m_widthField = 0;
void CustomerOrder::display(std::ostream& os) const
{
	os << m_name << " - " << m_product << std::endl;
	std::string status{};
	
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_IstItem[i]->m_isFilled)
			status = "FILLED";
		else
			status = "MISSING";
		os << "[" << std::right << std::setfill('0') << std::setw(6) << m_IstItem[i]->m_serialNumber
			<< std::setfill(' ') << "] " << std::left << std::setw(m_widthField) << m_IstItem[i]->m_itemName << " - " << status
			<< std::endl;
			
	}
}
void CustomerOrder::setSave()
{
	m_name = {};
	m_product = {};
	m_cntItem = 0;
	m_IstItem = nullptr;
}

CustomerOrder::CustomerOrder()
{
	setSave();
}

CustomerOrder::CustomerOrder(std::string& str)
{
	Utilities utilities;
	bool more = false;
	std::string temp = str;
	size_t ind = 0;

	m_name = utilities.extractToken(str, ind, more);
	
	if (more)
	{
		m_product = utilities.extractToken(str, ind, more);
		
		size_t indTemp = ind;
		size_t count = 0;

		//checking number of items
		while (more)
		{
			count++;
			utilities.extractToken(str, ind, more);
			
		}
		if (count > 0)
		{
			m_IstItem = new Item * [count];
			m_cntItem = count;
			for (size_t i = 0; i < count; i++)
			{
				m_IstItem[i] = new Item(utilities.extractToken(str, indTemp, more));
				
			}
		}
		if (utilities.getFieldWidth() > m_widthField)
			m_widthField = utilities.getFieldWidth() + 3;
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder&) 
{
	throw("Copy constractor is not allowed!\n");
}

CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept
{
	if (this != &co) {
		m_name = co.m_name;
		m_cntItem = co.m_cntItem;
		m_product = co.m_product;
		m_IstItem = co.m_IstItem;
		co.m_IstItem = nullptr;
	}
	else {
		setSave();
	}
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept
{

	if (this != &co) {
		if (m_IstItem != nullptr) {
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (m_IstItem[i] != nullptr)
					delete m_IstItem[i];
			}
			delete[] m_IstItem;
		}
		m_IstItem = co.m_IstItem;
		co.m_IstItem = nullptr;
		m_name = co.m_name;
		m_cntItem = co.m_cntItem;
		m_product = co.m_product;
		
		
	}
	return *this;
}

CustomerOrder::~CustomerOrder()
{
	if (m_IstItem != nullptr) {
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_IstItem[i] != nullptr)
				delete m_IstItem[i];
		}
		delete[] m_IstItem;
	}
}

bool CustomerOrder::isOrderFilled() const
{
	bool isFilled = true;
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_IstItem[i]->m_isFilled == false)
			isFilled = false;
	}
	return isFilled;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
	bool isFilled = false;
	bool isFound = false;
	if (m_IstItem != nullptr) {
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_IstItem[i]->m_itemName == itemName)
			{
				isFilled = m_IstItem[i]->m_isFilled;
				isFound = true;
			}
		}
	}

	if (!isFound)
		isFilled = true;
	return isFilled;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{
	if (m_IstItem != nullptr) {
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_IstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_IstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_IstItem[i]->m_isFilled = true;
					os << std::right << std::setw(11) << "Filled " << m_name << ", " << m_product << " [" << m_IstItem[i]->m_itemName << "]" << std::endl;
				}
				else
					os << std::setw(19) << "Unable to fill" << m_name << ", " << m_product << " [" << m_IstItem[i]->m_itemName << "]";


			}
		}
	}
}
