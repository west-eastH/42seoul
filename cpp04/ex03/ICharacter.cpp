
	AMateria::AMateria()
	{
		this->_type = std::string("Default");
		std::cout << "AMateria constructor called" << std::endl;
	}
	
	AMateria::~AMateria()
	{
		std::cout << "AMateria Destructor called" << std::endl;
	}
	
	AMateria::AMateria(const AMateria &origin)
	{
		this->_type = std::string(origin.getType());
		std::cout << "AMateria Copy constructor called" << std::endl;
	}
	
	AMateria& AMateria::operator=(const AMateria &origin)
	{
		if (this != &origin)
		{
			this->_type = std::string(origin.getType());
			std::cout << "AMateria Copy assignment operator called" << std::endl;
		}
		return *this;	
	}
	