#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(int argc, char *argv[])
{
	if (argc != 2)
		throw std::invalid_argument("Error: could not open file.");
	makeVector("data.csv", DATA);
	makeVector(argv[1], INPUT);
	dataToNumber();
	start();
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::splitInput(std::string& line, bool flag)
{
	std::vector<sp>* vec;
	std::string sep;
	if (flag == DATA)
	{
		if (line == "date,exchange_rate")
			return ;
		vec = &_stringData;
		sep = ",";
	}
	else
	{
		vec = &_input;
		sep = " | ";
	}
	if (line == "")
		return ;
	size_t pos = line.find(sep);
	if (pos == std::string::npos)
	{
		vec->push_back(make_pair(line, ""));
		return ;
	}
	std::string date = line.substr(0, pos);
	std::string val = line.substr(pos + sep.length());
	vec->push_back(make_pair(date, val));
}

void BitcoinExchange::makeVector(std::string fileName, bool flag)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		if (flag == INPUT)
		{
			getline(file, line);
			if (line != "date | value")
				throw std::invalid_argument("Error: invalid format.");
		}
		while (!file.eof())
		{
			getline(file, line);
			splitLine(line, flag);
		}
		file.close();
		return ;
	}
	throw std::invalid_argument("Error: could not open file.");
}

void BitcoinExchange::start()
{
	for (size_t i = 0; i < _input.size(); i++)
	{
		if (isValidDate(_input[i].first) && isValidValue(_input[i].second))
			exchange(_input[i].first, _input[i].second);
	}
	
}

void BitcoinExchange::exchange(std::string &stringDate, std::string &stringVal)
{
	std::string temp = stringDate;
	size_t pos = temp.find("-");
	while (pos != std::string::npos)
	{
		temp.erase(pos, 1);
		pos = temp.find("-");
	}
	int date = std::atoi(temp.c_str());
	char* pEnd;
	double val = std::strtod(stringVal.c_str(), &pEnd);
	for (size_t i = _numberData.size() - 1; i >= 0; i--)
	{
		if (_numberData[i].first <= date)
		{
			std::cout << stringDate << " => " << stringVal << " = " << _numberData[i].second * val << std::endl;
			return ;
		}
	}
	std::cout << stringDate << " => " << stringVal << " = 0.0" << std::endl;
}

void BitcoinExchange::dataToNumber()
{
	for (size_t i = 0; i < _stringData.size(); i++)
	{
		std::string temp = _stringData[i].first;
		size_t pos = temp.find("-");
		while (pos != std::string::npos)
		{
			temp.erase(pos, 1);
			pos = temp.find("-");
		}
		int date = std::atoi(temp.c_str());
		char* pEnd;
		double val = std::strtod(_stringData[i].second.c_str(), &pEnd);
		_numberData.push_back(std::make_pair(date, static_cast<float>(val)));
	}
}

bool BitcoinExchange::isValidDate(std::string date)
{
	std::vector<int>dateVector;
    std::stringstream ss(date);
    std::string temp;
	if (date.front() == '-')
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	int cnt = 0;
	for (size_t i = 0; i < date.length(); i++)
	{
		if (date[i] < '0' || date[i] > '9')
		{
			if (date[i] == '-' && cnt < 3)
			{
				cnt++;
				continue ;
			}
			std::cout << "Error: bad input => " << date << std::endl;
			return false;
		}
	}
    while (getline(ss, temp, '-'))
	{
		if (temp.length() == 0)
		{
			std::cout << "Error: bad input => " << date << std::endl;
			return false;
		}
        dateVector.push_back(std::atoi(temp.c_str()));
    }
	if (!isValidDay(dateVector))
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidValue(std::string val)
{
	if (val.front() == '-')
	{
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	else if (val.front() == '.')
	{
		std::cout << "Error: bad input => " << val << std::endl;
		return false;
	}
	size_t cnt = 0;
	for (size_t i = 0; i < val.length(); i++)
	{
		if (val[i] < '0' || val[i] > '9')
		{
			if (cnt == 0 && val[i] == '.')
			{
				cnt++;
				continue ;
			}
			std::cout << "Error: bad input => " << val << std::endl;
			return false;
		}
	}
	if (std::stod(val) > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidDay(std::vector<int>& dateVector)
{
	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (dateVector.size() != 3)
		return false;
	if (dateVector[1] > 12 || dateVector[2] > month[dateVector[1] - 1])
	{
		if (dateVector[1] == 2 && dateVector[2] == 29)
		{
			if (dateVector[0] % 4 == 0)
			{
				if (dateVector[0] % 100 == 0)
				{
					if (dateVector[0] % 400 == 0)
						return true;
					return false;
				}
				return true;
			}
			return false;
		}
		return false;
	}
	return true;
}