#pragma once

#include <iostream>
#include <exception>
#include <vector>
#include <fstream>
#include <sstream>

#define DATA 0
#define INPUT 1
typedef std::pair<std::string, std::string> p;

class BitcoinExchange
{
	std::vector<p> _data;
	std::vector<p> _input;

	private:		
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& origin);
		BitcoinExchange& operator=(const BitcoinExchange& origin);
	public:
		~BitcoinExchange();
		BitcoinExchange(int argc, char *argv[]);
		void makeVector(std::string fileName, bool flag);
		std::pair<std::string, std::string> splitLine(std::string& line, std::string sep);
		void start();
		void exchange();
		bool isValidDate(std::string date);
		bool isValidValue(std::string val);
		bool isValidDay(std::vector<int>& dateVector);
};
