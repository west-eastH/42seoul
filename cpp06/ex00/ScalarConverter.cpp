#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &origin) {(void)origin;}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter &origin) {(void)origin; return *this;}
ScalarConverter::~ScalarConverter() {}

bool isPseudo(std::string &literal)
{
	if (literal == "-nan" || literal == "+nan" || literal == "nan" || \
		literal == "-nanf" || literal == "+nanf" || literal == "nanf" || \
		literal == "-inff" || literal == "+inff" || literal == "inff" || \
		literal == "-inf" || literal == "+inf" || literal == "inf")
	{
		if (literal.front() == '+')
			literal = literal.substr(1);
		std::cout << "char : impossible" << std::endl;
		std::cout << "int : impossible" << std::endl;
		if (literal == "-inff" || literal == "inff" || literal == "nanf")
		{
			std::cout << "float : " << literal << std::endl;
			std::cout << "double : " << literal.erase(literal.size() - 1, 1) << std::endl;
		}
		else
		{
			std::cout << "float : " << literal << "f" << std::endl;
			std::cout << "double : " << literal << std::endl;
		}
		return true;
	}
	return false;
}

bool isChar(std::string& literal)
{
	if ((literal.front() < '0' || literal.front() > '9') && (literal.front() != '-' && literal.front() != '+'))
	{
		//한글자인 경우
		if (literal.size() == 1)
		{
			char c = literal.front();
			if (c < -128 || c > 127)
				std::cout << "char : impossible" << std::endl;
			else if (c < 32)
				std::cout << "char : Non displayable" << std::endl;
			else
				std::cout << "char : " << c << std::endl;
			std::cout << "int : " << static_cast<int>(c) << std::endl;
			std::cout << "float : " << static_cast<float>(c) << "f" << std::endl;
			std::cout << "double : " << static_cast<double>(c) << std::endl;
		}
		//2개 이상의 문자로 이루어진 문자열
		else
			throw (1);
		return true;
	}
	return false;
}

void countPoint(std::string& literal)
{
	int count = 0;

	if (literal.back() == '.')
			throw (1);
	for (size_t i = 0; (i = literal.find('.', i)) != std::string::npos; i++)
	{
        count++;
		if (count > 1 || literal[i + 1] < '0' || literal[i + 1] > '9')
			throw (1);
    }
}

void printNum(double data)
{
	if (data < -987654321 || data > 987654321)
		std::cout << "int : impossible" << std::endl;
	else
		std::cout << "int : " << static_cast<int>(data) << std::endl;
	std::cout << "float : " << static_cast<float>(data) << "f" << std::endl;
	std::cout << "double : " << static_cast<double>(data) << std::endl;
}

void dataRangeCheck(double& data)
{
	if (data < -128 || data > 127)
		std::cout << "char : impossible" << std::endl;
	else if (data < 32)
		std::cout << "char : Non displayable" << std::endl;
	else
		std::cout << "char : " << static_cast<char>(data) << std::endl;
	if (data > 987654321)
		data = HUGE_VAL;
	else if (data < -987654321)
		data = -HUGE_VAL;
}

void ScalarConverter::convert(std::string literal)
{
	double	data;
	char	*pEnd;

	std::cout << std::fixed;
	std::cout.precision(1);
	//문자열로 inf나 nan들어올 때
	if (isPseudo(literal))
		return;
	//문자로 시작하는 경우
	if (isChar(literal))
		return ;
	//.개수가 2개 이상인 경우 || 마지막 글자가 .인 경우
	countPoint(literal);
	data = std::strtod(literal.c_str(), &pEnd);
	//문자열 중간에 숫자가 아닌 문자가 들어왔을경우("f" 제외)
	if (std::strcmp(pEnd, "") != 0)
	{
		if (std::strcmp(pEnd, "f") != 0)
			throw (1);
	}
	dataRangeCheck(data);
	printNum(data);
}
