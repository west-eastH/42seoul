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

Fixed::Fixed(const int num)
{
	std::cout << "Int constructor called" << std::endl;
	this->_rawBits = num << _fractionalBits;
}

Fixed::Fixed(const float num)
{
	std::cout << "Float constructor called" << std::endl;
	this->_rawBits = roundf(num * (1 << _fractionalBits));
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
	return (this->_rawBits);
}

void Fixed::setRawBits( int const raw )
{
	this->_rawBits = raw;
}

float Fixed::toFloat( void ) const
{
	float result;
	result = (float)this->getRawBits() / (1 << _fractionalBits);
	return result;
}

int Fixed::toInt( void ) const
{
	int result;
	result = this->getRawBits() >> _fractionalBits;
	return result;
}

std::ostream	&operator<<(std::ostream &out, const Fixed &ref)
{
	out << ref.toFloat();
	return (out);
}