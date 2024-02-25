#include "Fixed.hpp"

Fixed::Fixed()
{
	this->_rawBits = 0;
}

Fixed::~Fixed()
{
}

Fixed::Fixed(const Fixed &origin)
{
	this->_rawBits = origin.getRawBits();
}

Fixed::Fixed(const int num)
{
	this->_rawBits = num << _fractionalBits;
}

Fixed::Fixed(const float num)
{
	this->_rawBits = roundf(num * (1 << _fractionalBits));
}

Fixed& Fixed::operator=(const Fixed &origin)
{
	if (this != &origin)
	{

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


bool Fixed::operator>(const Fixed &ref) const
{
	return (getRawBits() > ref.getRawBits());
}

bool Fixed::operator<(const Fixed &ref) const
{
	return (getRawBits() < ref.getRawBits());
}

bool Fixed::operator>=(const Fixed &ref) const
{
	return (getRawBits() >= ref.getRawBits());
}

bool Fixed::operator<=(const Fixed &ref) const
{
	return (getRawBits() <= ref.getRawBits());
}

bool Fixed::operator==(const Fixed &ref) const
{
	return (getRawBits() == ref.getRawBits());
}

bool Fixed::operator!=(const Fixed &ref) const
{
	return (getRawBits() != ref.getRawBits());
}

Fixed Fixed::operator+(const Fixed &ref)
{
	Fixed temp;
	temp.setRawBits(getRawBits() + ref.getRawBits());
	return temp;
}

Fixed Fixed::operator-(const Fixed &ref)
{
	Fixed temp;
	temp.setRawBits(getRawBits() - ref.getRawBits());
	return temp;
}

Fixed Fixed::operator*(const Fixed &ref)
{
	Fixed temp;
	float num = toFloat() * ref.toFloat();
	temp.setRawBits(roundf(num * (1 << _fractionalBits)));
	return temp;
}

Fixed Fixed::operator/(const Fixed &ref)
{
	Fixed temp;
	float num = toFloat() / ref.toFloat();
	temp.setRawBits(roundf(num * (1 << _fractionalBits)));
	return temp;
}

Fixed &Fixed::operator--()
{
	setRawBits(getRawBits() - 1);
	return *this;
}
Fixed Fixed::operator--(int)
{
	Fixed temp = *this;
	setRawBits(getRawBits() - 1);
	return temp;
}

Fixed &Fixed::operator++()
{
	setRawBits(getRawBits() + 1);
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp = *this;
	setRawBits(getRawBits() + 1);
	return temp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return a;
	return b;
}

const Fixed &Fixed::min(Fixed const &a, Fixed const &b)
{
	if (a < b)
		return a;
	return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return a;
	return b;
}

const Fixed &Fixed::max(Fixed const &a, Fixed const &b)
{
	if (a > b)
		return a;
	return b;
}
