#pragma once

#include <iostream>
#include <string>

class Fixed
{
	private:
		int _rawBits;
		static const int _fractionalBits = 8;
	public:
		Fixed();
		~Fixed();
		Fixed(const Fixed &origin);
		Fixed &operator=(const Fixed &origin);
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};