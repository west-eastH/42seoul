#include <iostream>
#include <ctime>
#include "Account.hpp"

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

void print_time()
{
	time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    
	std::cout << "[" << t->tm_year + 1900;
	if (t->tm_mon + 1 < 10)
		std::cout << "0";
	std::cout << t->tm_mon + 1;
	if (t->tm_mday < 10)
		std::cout << "0";
	std::cout << t->tm_mday << "_";
	if (t->tm_hour < 10)
		std::cout << "0";
	std::cout << t->tm_hour;
	if (t->tm_min < 10)
		std::cout << "0";
	std::cout << t->tm_min;
	if (t->tm_sec < 10)
		std::cout << "0";
	std::cout << t->tm_sec << "] ";
}

int	Account::getNbAccounts( void )
{
	return Account::_nbAccounts;
}
int	Account::getTotalAmount( void )
{
	return Account::_totalAmount;
}
int	Account::getNbDeposits( void )
{
	return Account::_totalNbDeposits;
}
int	Account::getNbWithdrawals( void )
{
	return Account::_totalNbWithdrawals;
}

void	Account::displayAccountsInfos( void )
{
	print_time();
	std::cout << "accounts:" << Account::getNbAccounts() << ";total:" << getTotalAmount() << ";deposits:" << getNbDeposits() << ";withdrawals:" << getNbWithdrawals() << "\n";
}

void	Account::displayStatus( void ) const
{
	print_time();
	std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";deposits:" << this->_nbDeposits << ";withdrawals:" << this->_nbWithdrawals << "\n";
}
Account::Account( int initial_deposit )
{
	this->_accountIndex = Account::_nbAccounts;
	Account::_nbAccounts++;
	Account::_totalAmount += initial_deposit;
	this->_amount = initial_deposit;
	print_time();
	std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";created\n";
	this->_nbWithdrawals = 0;
}
Account::~Account( void )
{
	print_time();
	std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";closed\n";
}

Account::Account( void )
{
	this->_accountIndex = Account::_nbAccounts;
	Account::_nbAccounts++;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
	print_time();
	std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";created\n";
}


void	Account::makeDeposit( int deposit )
{
	int p_amount = this->_amount;
	this->_nbDeposits = 1;
	this->_amount = p_amount + deposit;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;
	print_time();
	std::cout << "index:" << this->_accountIndex << ";p_amount:" << p_amount << ";deposit:" << deposit << ";amount:" << this->_amount << ";nb_deposits:" << this->_nbDeposits << "\n";
}
bool	Account::makeWithdrawal( int withdrawal )
{
	int p_amount = this->_amount;
	if (this->_amount < withdrawal)
	{
		print_time();
		std::cout << "index:" << this->_accountIndex << ";p_amount:" << p_amount << ";withdrawal:" << "refused\n";
		return (0);
	}
	this->_amount = p_amount - withdrawal;
	this->_nbWithdrawals = 1;

	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;
	print_time();
	std::cout << "index:" << this->_accountIndex << ";p_amount:" << p_amount << ";withdrawal:" << withdrawal << ";amount:" << this->_amount << ";nb_withdrawals:" << this->_nbWithdrawals << "\n";
	return 1;
}
