#pragma once

#include <iostream>
#include <string>
#include <cmath>

class Fixed
{
	private:
		int _rawBits;
		static const int _fractionalBits = 8;
	public:
		Fixed();
		Fixed(const int num);
		Fixed(const float num);
		~Fixed();
		Fixed(const Fixed &origin);
		Fixed &operator=(const Fixed &origin);
		int getRawBits( void ) const;
		void setRawBits( int const raw );
		float toFloat( void ) const;
		int toInt( void ) const;

		bool operator>(const Fixed &ref) const;
		bool operator<(const Fixed &ref) const;
		bool operator>=(const Fixed &ref) const;
		bool operator<=(const Fixed &ref) const;
		bool operator==(const Fixed &ref) const;
		bool operator!=(const Fixed &ref) const;

		Fixed operator+(const Fixed &ref);
		Fixed operator-(const Fixed &ref);
		Fixed operator*(const Fixed &ref);
		Fixed operator/(const Fixed &ref);

		Fixed &operator--();
		Fixed operator--(int);
		Fixed &operator++();
		Fixed operator++(int);

		static Fixed &min(Fixed &a, Fixed &b);
		const static Fixed &min(Fixed const &a, Fixed const &b);
		static Fixed &max(Fixed &a, Fixed &b);
		const static Fixed &max(Fixed const &a, Fixed const &b);
};
std::ostream	&operator<<(std::ostream &out, const Fixed &ref);