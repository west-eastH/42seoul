#pragma once

#include <iostream>
#include <exception>
#include <vector>
#include <fstream>
#include <sstream>

#define DATA 0
#define INPUT 1
typedef std::pair<std::string, std::string> sp;
typedef std::pair<int, float> np;

class BitcoinExchange
{
	std::vector<sp> _input;
	std::vector<sp> _stringData;
	std::vector<np> _numberData;

	private:		
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& origin);
		BitcoinExchange& operator=(const BitcoinExchange& origin);
	public:
		~BitcoinExchange();
		BitcoinExchange(int argc, char *argv[]);
		void makeVector(std::string fileName, bool flag);
		void splitLine(std::string& line, bool flag);
		void start();
		void exchange(std::string& stringDate, std::string& stringVal);
		void dataToNumber();
		bool isValidDate(std::string date);
		bool isValidValue(std::string val);
		bool isValidDay(std::vector<int>& dateVector);
};
