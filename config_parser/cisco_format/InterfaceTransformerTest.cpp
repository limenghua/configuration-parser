/*******************************************************************
*  Copyright(c) 2010-2017 Netbrain
*  All rights reserved.
*
*  文件名称: InterfaceTransformerTest.cpp
*  简要描述:
*
*  当前版本:
*  作者: limenghua
*  日期: 2017/05/07
*  说明:
*
******************************************************************/
#include <gtest/gtest.h>
#include "InterfaceTransformer.h"
#include "TestUtil.h"

TEST(InterfaceTransformerTest, Constructor)
{

	const std::string sourceDoc =
	R"({
		"key":"interface",
		"interface":"g/0.1"
	})";

	const std::string expectDestDoc =
	R"({
		"interfaces":
		[
			{"interface":"g/0.1"}
		]
	})";

	InterfaceTransformer t;

	Json::Value sourceJson = CreateJsonFromString(sourceDoc);
	Json::Value expectDestJson = CreateJsonFromString(expectDestDoc);

	Json::Value destJson = t.Transform(sourceJson);
	
	EXPECT_EQ(destJson, expectDestJson);
}

TEST(InterfaceTransformerTest, ChildShouldMergeIntoRoot)
{

	const std::string sourceDoc =
		R"({
		"key":"interface",
		"interface":"g/0.1",
		"childs":
		[
			{"key":"ip adress","ip adress":"127.0.0.1 255.255.255.0"},
			{"key":"security-level","security-level":"0"}
		]
	})";

	const std::string expectDestDoc =
		R"({
		"interfaces":
		[
			{"interface":"g/0.1","ip adress":"127.0.0.1 255.255.255.0","security-level":"0"}
		]
	})";

	InterfaceTransformer t;

	Json::Value sourceJson = CreateJsonFromString(sourceDoc);
	Json::Value expectDestJson = CreateJsonFromString(expectDestDoc);

	Json::Value destJson = t.Transform(sourceJson);

	EXPECT_EQ(destJson, expectDestJson);
}

