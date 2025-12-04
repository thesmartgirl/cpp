#include <iostream>
#include <string>

int main(int ac, char **argv) 
{
	std::string input_text;
	if (ac > 1)
	{
		for(int i = 1; i < ac; i++)
		{
			input_text = argv[i];
			std::c(input_text.begin(), input_text.end(), input_text.begin(), ::toupper);
			std::cout << input_text;
			if(i < ac - 1)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	return 0;
}