#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "ConfigureParser/ConfigureParser.h"

class Performance : public ::testing::Test 
{
protected:
	virtual void SetUp() 
	{
	}
	virtual void TearDown()
	{
	}

	std::stringstream _ssin;
	std::stringstream _ssout;
};

TEST_F(Performance, Test)
{
	std::ifstream fin("example.config");
	std::ofstream fout("example.json");
	ParseConfigToJson(fin, fout);
}