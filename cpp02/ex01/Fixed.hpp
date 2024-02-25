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
};
std::ostream	&operator<<(std::ostream &out, const Fixed &ref);