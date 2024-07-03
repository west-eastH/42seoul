#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(int argc)
{
	if (argc != 2)
		throw std::invalid_argument("Error: could not open file.");
	init();
	dataToNumber();
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::init()
{
	std::ifstream file("data.csv");

	if (file.is_open())
	{
		std::string line;
		while (!file.eof())
		{
			getline(file, line);
			splitData(line);
		}
		file.close();
		return ;
	}
	throw std::invalid_argument("Error: could not open file.");
}

void BitcoinExchange::splitData(std::string& line)
{
	std::map<std::string, std::string>* my_map;
	std::string sep;

	if (line == "date,exchange_rate")
		return ;
	my_map = &_stringData;
	sep = ",";
	if (line == "")
		return ;
	size_t pos = line.find(sep);
	if (pos == std::string::npos)
	{
		my_map->insert(make_pair(line, ""));
		return ;
	}
	std::string date = line.substr(0, pos);
	std::string val = line.substr(pos + sep.length());
	my_map->insert(std::make_pair(date, val));
}

void BitcoinExchange::dataToNumber()
{
	for (std::map<std::string, std::string>::iterator it = _stringData.begin(); it != _stringData.end(); ++it)
	{
		std::string temp = it->first;
		size_t pos = temp.find("-");
		while (pos != std::string::npos)
		{
			temp.erase(pos, 1);
			pos = temp.find("-");
		}
		int date = std::atoi(temp.c_str());
		char* pEnd;
		double val = std::strtod(it->second.c_str(), &pEnd);
		_numberData.insert(std::make_pair(date, static_cast<float>(val)));
	}
}

void BitcoinExchange::splitInput(std::string& line)
{
	std::string sep;

	sep = " | ";
	if (line == "")
		return ;
	size_t pos = line.find(sep);
	if (pos == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}
	std::string date = line.substr(0, pos);
	std::string val = line.substr(pos + sep.length());

	if (isValidDate(date) && isValidValue(val))
		exchange(date, val);
}

void BitcoinExchange::start(std::string filename)
{
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		getline(file, line);
		if (line != "date | value")
			throw std::invalid_argument("Error: invalid format.");
		while (!file.eof())
		{
			getline(file, line);
			splitInput(line);
		}
		file.close();
		return ;
	}
	throw std::invalid_argument("Error: could not open file.");
}

bool BitcoinExchange::isValidDate(std::string date)
{
	int dateArray[3];
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
	int i = 0;
    while (getline(ss, temp, '-'))
	{
		if (temp.length() == 0 || (i != 0 && temp.length() != 2))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			return false;
		}
        dateArray[i++] = (std::atoi(temp.c_str()));
    }
	if (!isValidDay(dateArray))
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

bool BitcoinExchange::isLeapYear(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return true;
            return false;
        }
        return true;
    }
    return false;
}

bool BitcoinExchange::isValidDay(int* dateArray)
{
	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (dateArray[0] < 2009 || (dateArray[0] == 2009 && dateArray[1] == 1 && dateArray[2] == 1))
		return false;
	if (dateArray[1] < 1 || dateArray[1] > 12)
		return false;
	else
	{
		if (dateArray[2] > month[dateArray[1] - 1])
		{
			if (dateArray[1] == 2 && dateArray[2] == 29 && isLeapYear(dateArray[0]))
				return true;
			return false;
		}
		return true;
	}
}

void BitcoinExchange::exchange(std::string stringDate, std::string stringVal)
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
	for (std::map<int, float>::reverse_iterator it = _numberData.rbegin(); it != _numberData.rend(); ++it)
	{
		if (it->first <= date)
		{
			std::cout << stringDate << " => " << stringVal << " = " << it->second * val << std::endl;
			return ;
		}
	}
	std::cout << stringDate << " => " << stringVal << " = 0.0" << std::endl;
}
