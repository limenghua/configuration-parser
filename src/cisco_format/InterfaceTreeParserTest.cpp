#include <gtest/gtest.h>
#include "InterfaceTreeParser.h"
#include <json/reader.h>
#include <json/writer.h>

TEST(InterfaceTreeParser, Constructor)
{
	const std::string content =
R"(interface inside
 nameif inside
 security-level 0
 ip address 172.26.7.10 255.255.255.0)";

	SentenceTree tree;
	ParseConfigToSentenceTree(content, tree);

	InterfaceTreeParser parser;
	auto root = parser.Parse(tree.GetChild(0));

	EXPECT_EQ(root["key"].asString(), "interface");
	EXPECT_EQ(root["interface"].asString(), "inside");

	auto childs = root["childs"];
	EXPECT_TRUE(childs.isArray());
	EXPECT_EQ(childs.size(), 3);

	auto nameif = childs[0];
	EXPECT_EQ(nameif["key"].asString(), "nameif");
	EXPECT_EQ(nameif["nameif"].asString(), "inside");

	auto security = childs[1];
	EXPECT_EQ(security["key"].asString(), "security-level");
	EXPECT_EQ(security["security-level"].asString(), "0");

	auto ip_address = childs[2];
	EXPECT_EQ(ip_address["key"].asString(), "ip address");
	EXPECT_EQ(ip_address["ip address"].asString(), "172.26.7.10 255.255.255.0");
}

const std::string configStr =
R"(
interface manage
 management-only
 nameif mgt
 security-level 100
 ip address 172.24.101.47 255.255.255.0 
)";

const std::string expectJson =
R"(
{	
	"key":"interface",
	"interface":"manage",
	"childs":[
		{"key":"management-only","management-only":"true"},
		{"key":"nameif","nameif":"mgt"},
		{"key":"security-level","security-level":"100"},
		{"key":"ip address","ip address":"172.24.101.47 255.255.255.0"}
	]
}
)";

TEST(InterfaceTreeParser, ParserStr)
{
	SentenceTree tree;
	ParseConfigToSentenceTree(configStr, tree);

	InterfaceTreeParser parser;
	auto root = parser.Parse(tree.GetChild(0));

	Json::Value expectRoot;
	Json::Reader reader;
	reader.parse(expectJson, expectRoot);

	EXPECT_EQ(root, expectRoot);
}
