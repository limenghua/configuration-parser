/******************************************************************* 
 *  Copyright(c) 2010-2017 Nethead
 *  All rights reserved. 
 *   
 *  文件名称: RootTreeParserTest.cpp
 *  简要描述: 
 *   
 *  当前版本: 
 *  作者: limenghua
 *  日期: 5/3/2017
 *  说明:  
 *
 ******************************************************************/
#include <gtest/gtest.h>

#include "RootTreeParser.h"
#include "ConfigureParser/ConfigureParser.h"

#include <json/reader.h>


static const std::string inputConfig =
R"(
!
version 15.0
!
hostname ASA-3
!
domain-name wr
!
interface out
 nameif outside
 security-level 0
 ip address 172.26.10.10 255.255.255.0
!
interface inside
 nameif inside
 security-level 0
 ip address 172.26.7.10 255.255.255.0
!
interface manage
 management-only
 nameif mgt
 security-level 100
 ip address 172.24.101.47 255.255.255.0
!
)";

static const std::string expectJson =
R"(
{
	"key":"root",
	"childs":[
		{"key":"version","version":"15.0"},
		{"key":"hostname","hostname":"ASA-3"},
		{"key":"origin","origin":"domain-name wr"},
		{"key":"interface",
		 "interface":"out",
		 "childs":[
			{"key":"nameif","nameif":"outside"},
			{"key":"security-level","security-level":"0"},
			{"key":"ip address","ip address":"172.26.10.10 255.255.255.0"}
		]
		},

		{"key":"interface",
		 "interface":"inside",
		 "childs":[
			{"key":"nameif","nameif":"inside"},
			{"key":"security-level","security-level":"0"},
			{"key":"ip address","ip address":"172.26.7.10 255.255.255.0"}
		]
		},

		{"key":"interface",
		 "interface":"manage",
		 "childs":[
			{"key":"management-only","management-only":"true"},
			{"key":"nameif","nameif":"mgt"},
			{"key":"security-level","security-level":"100"},
			{"key":"ip address","ip address":"172.24.101.47 255.255.255.0"}
		]
		}
	]
}
)";

TEST(RootTreeParserTest, Test)
{
	SentenceTree tree;
	ParseConfigToSentenceTree(inputConfig, tree);

	RootTreeParser parser;
	auto root = parser.Parse(tree);

	Json::Value expectRoot;
	Json::Reader reader;
	reader.parse(expectJson, expectRoot);

	EXPECT_EQ(root, expectRoot);
}