#include <gtest/gtest.h>
#include <sstream>
#include <json/reader.h>
#include "DefaultTreeParser.h"
#include "ConfigureParser/ConfigureParser.h"



TEST(DefaultTreeParser, TreeHasNochild)
{
	SentenceTree tree("interface Ethernet0/0");

	DefaultTreeParser parser;

	Json::Value root = parser.Parse(tree);

	EXPECT_EQ(root["key"].asString(), "origin");
	EXPECT_EQ(root["origin"].asString(), "interface Ethernet0/0");
}

TEST(DefaultTreeParser, TreeHasOnlyOneChild)
{
	SentenceTree tree("interface Ethernet0/0");
	tree.AddChild("ip address 158.4.0.170 255.255.255.252");

	DefaultTreeParser parser;
	Json::Value root =	parser.Parse(tree);

	EXPECT_EQ(root["key"].asString(), "origin");
	EXPECT_EQ(root["origin"].asString(), "interface Ethernet0/0");
	EXPECT_FALSE(root["childs"].isNull());
}

TEST(DefaultTreeParser, JsonValueEqualEmpare)
{
	SentenceTree tree("interface Ethernet0/0");
	tree.AddChild("ip address 158.4.0.170 255.255.255.252");
	tree.AddChild("ip access-group 1 in");

	DefaultTreeParser parser;
	Json::Value root = parser.Parse(tree);

	EXPECT_EQ(root["key"].asString(), "origin");
	EXPECT_EQ(root["origin"].asString(), "interface Ethernet0/0");

	EXPECT_FALSE(root["childs"].isNull());

	std::string strDoc = 
R"({
	"key":"origin",
    "origin": "interface Ethernet0/0", 
    "childs": [
        {
			"key":"origin",
            "origin": "ip address 158.4.0.170 255.255.255.252"
        }, 
        {
			"key":"origin",
            "origin": "ip access-group 1 in"
        }
    ]
})";

	Json::Reader reader;
	Json::Value value;
	reader.parse(strDoc,value);

	EXPECT_EQ(root, value);
}

bool CheckConfigJsonParserResult(const std::string & strConfig, const std::string & strJson)
{
	std::stringstream ss(strConfig);

	SentenceTree tree;
	ParseConfigToSentenceTree(ss, tree);
	DefaultTreeParser parser;
	Json::Value root = parser.Parse(tree);

	Json::Reader reader;
	Json::Value value;
	reader.parse(strJson, value);

	return (root == value);
}


TEST(DefaultTreeParser, SomeComplextTest)
{
	std::string strConfig =
R"(
!
version 15.2
hostname example
!
object-group network netgrp1
 host 158.4.255.37
 host 158.4.255.38
!
interface Ethernet0/0
 ip address 158.4.0.170 255.255.255.252
 ip access-group 1 in
 ip access-group R3toR1 out
!
)";

std::string strDoc =
R"({
    "key": "origin",
	"origin":"",
    "childs": [
        {
			"key": "origin",
            "origin": "version 15.2"
        }, 
        {
			"key": "origin",
            "origin": "hostname example"
        }, 
        {
			"key": "origin",
            "origin": "object-group network netgrp1", 
            "childs": [
                {
					"key": "origin",
                    "origin": "host 158.4.255.37"
                }, 
                {
					"key": "origin",
                    "origin": "host 158.4.255.38"
                }
            ]
        }, 
        {
			"key": "origin",
            "origin": "interface Ethernet0/0", 
            "childs": [
                {
					"key": "origin",
                    "origin": "ip address 158.4.0.170 255.255.255.252"
                }, 
                {
					"key": "origin",
                    "origin": "ip access-group 1 in"
                }, 
                {
					"key": "origin",
                    "origin": "ip access-group R3toR1 out"
                }
            ]
        }
    ]
})";


bool ret = CheckConfigJsonParserResult(strConfig, strDoc);
EXPECT_TRUE(ret);
}




