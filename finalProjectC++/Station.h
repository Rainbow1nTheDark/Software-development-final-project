// Name: Alexander Balandin
// Seneca Student ID: 132145194
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef STATION_H
#define STATION_H
#include <iostream>
#include <string>
class Station
{
	int m_id;
	std::string m_itemName;
	std::string m_description;
	int m_serialNum;
	int m_itemsLeft;
	static int m_widthField;
	static int id_generator;
public:
	Station();
	// if I need at least one of the five, I probably need them all
	Station(Station& station) = delete;
	Station(Station&& station) noexcept;
	Station& operator=(Station&& station) = delete;
	Station& operator=(Station& station) = delete;
	~Station();

	explicit Station(const std::string& str);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
	void setSave();
	
	
};
#endif

