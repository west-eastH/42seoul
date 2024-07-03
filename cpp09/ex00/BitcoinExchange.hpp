#pragma once

#include <iostream>
#include <exception>
#include <fstream>
#include <map>
#include <sstream>

#define DATA 0
#define INPUT 1

class BitcoinExchange
{
	std::map<int, float> _numberData;
	std::map<std::string, std::string> _stringData;

	private:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& origin);
		BitcoinExchange& operator=(const BitcoinExchange& origin);
	public:
		~BitcoinExchange();
		BitcoinExchange(int argc);
		void init();
		void splitInput(std::string& line);
		void splitData(std::string& line);
		void readInput(std::string fileName, bool flag);
		void dataToNumber();
		void start(std::string filename);
		bool isValidDate(std::string date);
		bool isValidValue(std::string val);
		bool isValidDay(int* dateVector);
		bool isLeapYear(int year);
		void exchange(std::string stringDate, std::string stringVal);
};