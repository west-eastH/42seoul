#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange() {}

std::pair<std::string, std::string> BitcoinExchange::splitLine(std::string& line, std::string sep)
{
	size_t pos = line.find(sep);
	if (pos == std::string::npos)
		return make_pair(line, "");
	std::string date = line.substr(0, pos);
	std::string val = line.substr(pos + sep.length());
	return make_pair(date, val);
}

void BitcoinExchange::makeVector(std::string fileName, bool flag)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		while (!file.eof())
		{
			getline(file, line);
			if (flag == DATA)
				_data.push_back(splitLine(line, ","));
			else
				_input.push_back(splitLine(line, " | "));
		}
		file.close();
		return ;
	}
	throw std::invalid_argument("Error: could not open file.");
}

void testPrint(std::vector<p> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << "date : " << vec[i].first <<  " value : " << vec[i].second << std::endl;
}

void BitcoinExchange::start()
{
	for (size_t i = 0; i < _input.size(); i++)
	{
		if (_input[i].first != "date" && _input[i].second != "value")
		{
			if (isValidDate(_input[i].first) && isValidValue(_input[i].second))
				std::cout << "data : " << _input[i].first << " value : " << _input[i].second << std::endl;
		}
	}
	
}

// Error: not a positive number.
// Error: bad input => 2001-42-42
// 2012-01-11 => 1 = 7.1
// Error: too large a number.

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

BitcoinExchange::BitcoinExchange(int argc, char *argv[])
{
	if (argc != 2)
		throw std::invalid_argument("Error: could not open file.");
	makeVector("data.csv", DATA);
	makeVector(argv[1], INPUT);
	start();
	// testPrint(_data);
	// testPrint(_input);
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