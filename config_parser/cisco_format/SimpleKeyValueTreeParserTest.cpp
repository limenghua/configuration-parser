#include <gtest/gtest.h>
#include "SentenceTree.h"
#include "SimpleKeyValueParser.h"
#include <json/value.h>



TEST(SimpleKeyValueTreeParserTest, VersionParser)
{
	SimpleKeyValueTreeParser versionParser("version");
	SentenceTree tree("version 15.2");
	Json::Value root = versionParser.Parse(tree);

	EXPECT_FALSE(root.isNull());

	EXPECT_FALSE(root["key"].isNull());
	EXPECT_TRUE(root["key"].isString());
	EXPECT_EQ(root["key"].asString(), "version");

	EXPECT_FALSE(root["version"].isNull());
	EXPECT_TRUE(root["version"].isString());
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

void ToDie()
{
	int * p = nullptr;
	*p = 0;
}

TEST(DeathTest, ToDie)
{
	ASSERT_DEATH(ToDie(), "");
}