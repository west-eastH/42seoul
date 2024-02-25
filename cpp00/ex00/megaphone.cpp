#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		for (int i=1; i < argc; i++)
		{
			for (int j=0; j<(int)strlen(argv[i]); j++)
			{
				if (argv[i][j] >= 'a' && argv[i][j] <= 'z')
					std::cout << (char)toupper(argv[i][j]);
				else
					std::cout << argv[i][j];

			}
		}
	}
	std::cout << std::endl;
	return 0;
}