#include <gtest/gtest.h>
#include "SimpleKeyValueParser.h"

SimpleKeyValueTreeParser hostNameParser("hostname");

TEST(HostnameTreeParserTest, HostnameCommandShouldParseHostname)
{
	SentenceTree tree("hostname example");

	Json::Value root = hostNameParser.Parse(tree);

	EXPECT_FALSE(root.isNull());

	EXPECT_FALSE(root["key"].isNull());
	EXPECT_TRUE(root["key"].isString());
	EXPECT_EQ(root["key"].asString(), "hostname");

	EXPECT_FALSE(root["hostname"].isNull());
	EXPECT_TRUE(root["hostname"].isString());
	EXPECT_EQ(root["hostname"].asString(), "example");
}

TEST(HostnameTreeParserTest, NoHostnameCommandShouldThrow)
{
	SentenceTree tree("not a host example");

	EXPECT_THROW(hostNameParser.Parse(tree), std::exception);
}

//parse "no hostname"
TEST(HostnameTreeParserTest, ParserShouldEnableKeywordNo)
{
	SentenceTree tree("no hostname");
	Json::Value root = hostNameParser.Parse(tree);

	EXPECT_EQ(root["key"].asString(), "hostname");
	EXPECT_TRUE(root["hostname"].isNull());
}

TEST(HostnameTreeParserTest, OnlyHasEmptyHostname)
{
	SentenceTree tree("hostname");

	Json::Value root = hostNameParser.Parse(tree);

	EXPECT_FALSE(root.isNull());

	EXPECT_FALSE(root["key"].isNull());
	EXPECT_TRUE(root["key"].isString());
	EXPECT_EQ(root["key"].asString(), "hostname");

	EXPECT_FALSE(root["hostname"].isNull());
	EXPECT_TRUE(root["hostname"].isString());
	EXPECT_EQ(root["hostname"].asString(), "");

	SentenceTree tree2("hostname  ");
	root = hostNameParser.Parse(tree2);
	EXPECT_FALSE(root.isNull());

	EXPECT_FALSE(root["key"].isNull());
	EXPECT_TRUE(root["key"].isString());
	EXPECT_EQ(root["key"].asString(), "hostname");

	EXPECT_FALSE(root["hostname"].isNull());
	EXPECT_TRUE(root["hostname"].isString());
	EXPECT_EQ(root["hostname"].asString(), "");
}


