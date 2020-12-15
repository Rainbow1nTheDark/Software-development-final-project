// Name: Alexander Balandin
// Seneca Student ID: 132145194
// Seneca email: abalandin@myseneca.ca
// Date of completion: 11/10/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <climits>
#include "Utilities.h"
char Utilities::m_delimiter = '\n';
size_t Utilities::m_widthField = 1;
Utilities::Utilities()
{
}

void Utilities::setFieldWidth(size_t newWidth)
{
	m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{

	
	std::string token{};
	std::string::size_type ind = str.find(m_delimiter, next_pos);
	//if no data in between delimeters 
 	if (ind == std::string::npos)
	{
		token =str.substr(next_pos);
		more = false;
	}
	else
	{


		if (ind < str.length() && next_pos < str.length()) {
			token = str.substr(next_pos, ind - next_pos);
			more = true;
		}
		else
			more = false;
		next_pos = ++ind;
	}
	
	return token;
}

void Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;
}

char Utilities::getDelimiter()
{
	return m_delimiter;
}

