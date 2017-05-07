#include <iostream>
#include <fstream>

#include "ConfigureParser/ConfigureParser.h"

int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		std::cout << "command:"<<std::endl;
		std::cout<<"example.exe inputfile outputfile" << std::endl;
		return 0;
	}

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	ParseConfigToJson(fin, fout);
}