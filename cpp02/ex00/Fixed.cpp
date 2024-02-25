#include "Fixed.hpp"
Fixed::Fixed()
{
	this->_rawBits = 0;
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &origin)
{
	std::cout << "Copy constructor called" << std::endl;
	this->_rawBits = origin.getRawBits();
}

Fixed& Fixed::operator=(const Fixed &origin)
{
	if (this != &origin)
	{
		std::cout << "Copy assignment operator called" << std::endl;
		this->_rawBits = origin.getRawBits();
	}
	return *this;
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_rawBits);
}

void Fixed::setRawBits( int const raw )
{
	this->_rawBits = raw;
}