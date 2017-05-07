#include <gtest/gtest.h>
#include "TestUtil.h"

#include <json/json.h>

#include "ConfigureParser/ConfigureParser.h"

static void DoTest(const std::string & strConfig, const std::string & expectDestDoc)
{
	std::string destJsonDoc;
	ParseConfigToJson(strConfig, destJsonDoc);

	Json::Value destJson = CreateJsonFromString(destJsonDoc);
	Json::Value expectDestJson = CreateJsonFromString(expectDestDoc);

	EXPECT_EQ(destJson, expectDestJson);
}

TEST(ParseConfigToJsonTest, SimpleConfigure)
{
	std::string strConfig =
R"(
!
version 15.0
!
)";
	std::string strExpectDoc =
R"(
{"version":"15.0"}
)";

	DoTest(strConfig, strExpectDoc);
}

TEST(ParseConfigToJsonTest, ComplexConfigure)
{
	std::string strConfig =
		R"(
!
version 15.0
hostname example!
interface Loopback0
 ip address 158.4.255.44 255.255.255.255
)";
	std::string strExpectDoc =
		R"(
{
	"version":"15.0",
	"hostname":"example",
	"interfaces":
	[
		{"interface":"Loopback0","ip address":"158.4.255.44 255.255.255.255"}
	]
}
)";

	DoTest(strConfig, strExpectDoc);
}