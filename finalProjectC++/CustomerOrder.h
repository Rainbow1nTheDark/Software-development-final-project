// Name: Alexander Balandin
// Seneca Student ID: 132145194
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include <string>
#include "Station.h"
struct Item;
class CustomerOrder
{
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	Item** m_IstItem{ nullptr };
	static size_t m_widthField;
public:
	CustomerOrder();
	CustomerOrder(std::string&);
	CustomerOrder(const CustomerOrder&);
	CustomerOrder(CustomerOrder&&) noexcept;
	CustomerOrder& operator=(CustomerOrder&) = delete;
	CustomerOrder& operator=(CustomerOrder&&) noexcept;
	~CustomerOrder();
	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
	void setSave();
};
struct Item
{
	std::string m_itemName{};
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;
	Item() {};
	Item(const std::string& src) : m_itemName(src) {};
	

};
#endif

