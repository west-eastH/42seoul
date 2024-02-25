# ifndef PHONEBOOK_HPP 
#define PHONEBOOK_HPP
# include "Contact.hpp"
class PhoneBook
{
	private:
		int		idx;
		Contact con[8];
	public:
		PhoneBook();
		void start();
		int add();
		void print_data(std::string data, int pipe);
		int search();
		int detail();
};
#endif