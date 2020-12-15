// Name: Alexander Balandin
// Seneca Student ID: 132145194
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Station.h"
#include <iomanip>
#include <memory>
#include "Utilities.h"
int Station::m_widthField = 0;
int Station::id_generator = 0;
Station::Station() {
	setSave();
}
Station::~Station()
{
}
Station::Station(const std::string& str)
{
	m_id = ++id_generator;
	Utilities utilities;
	bool more = false;
	std::string temp = str;
	size_t start = 0;

	m_itemName = utilities.extractToken(temp, start, more);
	
	if (more) {

		m_serialNum = std::stoi(utilities.extractToken(temp, start, more));
		
		m_itemsLeft = std::stoi(utilities.extractToken(temp, start, more));
		
		

		m_description = utilities.extractToken(temp, start, more);

		if (static_cast<size_t>(m_widthField) < m_itemName.length())
		{
			m_widthField = m_itemName.length() + 1;
			utilities.setFieldWidth(m_widthField);
		}
		utilities.setFieldWidth(m_widthField);
		
	}
	else {
		setSave();
	}
}

const std::string& Station::getItemName() const
{
	
	return m_itemName;
}



unsigned int Station::getNextSerialNumber()
{

	return m_serialNum++;
}

unsigned int Station::getQuantity() const
{
	return m_itemsLeft;
}

void Station::updateQuantity()
{
	if (m_itemsLeft > 0)
		m_itemsLeft--;
}

void Station::display(std::ostream& os, bool full) const
{
	
	if (full)
	{
		os << std::right << "[" << std::setfill('0') << std::setw(3) << m_id << std::setfill(' ') << "] Item: " << std::setw(m_widthField)
			<< std::left << m_itemName << "[" << std::right << std::setfill('0') << std::setw(6) << m_serialNum << std::setfill(' ') << "] Quantity: " ;
		os << std::setw(m_widthField) << std::left << m_itemsLeft << "Description: "  << m_description;
	}
	else 
	{
		os  << "[" << std::setfill('0') << std::setw(3) << m_id << std::setfill(' ') << "] Item: " << std::setw(m_widthField)
			<< std::left << m_itemName << "[" <<  std::right << std::setfill('0') << std::setw(6) << m_serialNum << "]";
	}
	os << '\n';
}
void Station::setSave()
{
	m_description = {};
	m_id = 0;
	m_itemName = {};
	m_itemsLeft = 0;
	m_serialNum = 0;
}
//Station::Station(Station& station) noexcept
//{
//	*this = station;
//}
Station::Station(Station&& station) noexcept
{
	if (this != &station) {
		
		m_itemName = station.m_itemName;

		
		m_description = station.m_description;

		m_id = station.m_id;
		m_itemsLeft = station.m_itemsLeft;
		m_serialNum = station.m_serialNum;

		
	}
	else {
		setSave();
	}
}
//Station& Station::operator=(Station&& station) noexcept
//{
//	if (this != &station) {
//		delete[] m_itemName;
//		m_itemName = station.m_itemName;
//
//		delete[] m_description;
//		m_description = station.m_description;
//
//		m_id = station.m_id;
//		m_itemsLeft = station.m_itemsLeft;
//		m_serialNum = station.m_serialNum;
//
//		station.m_itemName = nullptr;
//		station.m_description = nullptr;
//	}
//	return *this;
//}
//Station& Station::operator=(Station& station) noexcept
//{
//	delete[] m_itemName;
//	m_itemName = new char[strlen(station.m_itemName) + 1];
//	strcpy(m_itemName, station.m_itemName);
//
//	delete[] m_description;
//	m_description = new char[strlen(station.m_description) + 1];
//	strcpy(m_description, station.m_description);
//
//	m_id = station.m_id;
//	m_itemsLeft = station.m_itemsLeft;
//	m_serialNum = station.m_serialNum;
//
//	
//	return *this;
//}
