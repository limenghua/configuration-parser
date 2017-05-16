#include <gtest/gtest.h>
#include "ConfigureParser/SentenceTree.h"
#include "SimpleKeyValueParser.h"
#include <json/value.h>



TEST(SimpleKeyValueTreeParserTest, VersionParser)
{
	SimpleKeyValueTreeParser versionParser("version");
	SentenceTree tree("version 15.2");
	Json::Value root = versionParser.Parse(tree);
	
	EXPECT_EQ(root["key"].asString(), "version");
	EXPECT_EQ(root["version"].asString(), "15.2");
}

TEST(SimpleKeyValueTreeParserTest, IpAdress)
{
	SimpleKeyValueTreeParser parser("ip address");
	SentenceTree tree("ip address 158.4.0.170 255.255.255.252");
	Json::Value root = parser.Parse(tree);

	EXPECT_EQ(root["key"].asString(), "ip address");
	EXPECT_EQ(root["ip address"].asString(), "158.4.0.170 255.255.255.252");
}

TEST(SimpleKeyValueTreeParserTest, ManagementOnly)
{
	SimpleKeyValueTreeParser parser("management-only","true");
	SentenceTree tree("management-only");
	Json::Value root = parser.Parse(tree);

	EXPECT_EQ(root["key"].asString(), "management-only");
	EXPECT_EQ(root["management-only"].asString(), "true");
}

