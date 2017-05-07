#include <gtest/gtest.h>

#include "RootTransformer.h"
#include "TestUtil.h"

#include <iostream>

static void DoTest(const std::string & sourceDoc, const std::string & expectDestDoc)
{
	RootTransformer t;

	Json::Value sourceJson = CreateJsonFromString(sourceDoc);
	Json::Value expectDestJson = CreateJsonFromString(expectDestDoc);

	Json::Value destJson = t.Transform(sourceJson);

	EXPECT_EQ(destJson, expectDestJson);

}

TEST(RootTransformerTest, Constorctor)
{
	const std::string sourceDoc =
	R"(
		{
			"key":"root",
			"childs":
			[
				{"key":"version","version":"15.1"},
				{"key":"hostname","hostname":"device1"}
			]
		}
	)";

	const std::string expectDestDoc =
		R"(
			{"version":"15.1","hostname":"device1"}
		)";

	DoTest(sourceDoc, expectDestDoc);


}

TEST(RootTransformerTest, OriginContentShoudAppendToChilds)
{
	const std::string sourceDoc =
		R"(
		{
			"key":"root",
			"childs":
			[
				{"key":"version","version":"15.1"},
				{"key":"hostname","hostname":"device1"},
				{"key":"origin","origin":"no ip domain lookup"},
				{"key":"origin","origin":"multilink bundle-name authenticated"}
			]
		}
	)";

	const std::string expectDestDoc =
		R"(
		{
			"version":"15.1",
			"hostname":"device1",
			"childs":
			[
				{"key":"origin","origin":"no ip domain lookup"},
				{"key":"origin","origin":"multilink bundle-name authenticated"}
			]
		}
		)";

	DoTest(sourceDoc, expectDestDoc);

}



TEST(RootTransformerTest, InterfaceFiledsShouldTransformCorrect)
{
	const std::string sourceDoc =
		R"(
		{
			"key":"root",
			"childs":
			[
				{"key":"version","version":"15.1"},
				{"key":"hostname","hostname":"device1"},
				{
					"key":"interface",
					"interface":"g/0.1",
					"childs":
					[
						{"key":"ip adress","ip adress":"127.0.0.1 255.255.255.0"},
						{"key":"security-level","security-level":"0"}
					]
				},
				{
					"key":"interface",
					"interface":"g/1.1",
					"childs":
					[
						{"key":"ip adress","ip adress":"127.0.1.1 255.255.255.0"},
						{"key":"security-level","security-level":"0"}
					]
				}

			]
		}
	)";

	const std::string expectDestDoc =
		R"(
		{
			"version":"15.1",
			"hostname":"device1",
			"interfaces":
			[
				{"interface":"g/0.1","ip adress":"127.0.0.1 255.255.255.0","security-level":"0"},
				{"interface":"g/1.1","ip adress":"127.0.1.1 255.255.255.0","security-level":"0"}
			]
		}
		)";


	DoTest(sourceDoc, expectDestDoc);
}

TEST(RootTransformerTest, OverallTest)
{
	const std::string sourceDoc =
		R"(
		{
			"key":"root",
			"childs":
			[
				{"key":"version","version":"15.1"},
				{"key":"hostname","hostname":"device1"},
				{
					"key":"interface",
					"interface":"g/0.1",
					"childs":
					[
						{"key":"ip adress","ip adress":"127.0.0.1 255.255.255.0"},
						{"key":"security-level","security-level":"0"}
					]
				},
				{
					"key":"interface",
					"interface":"g/1.1",
					"childs":
					[
						{"key":"ip adress","ip adress":"127.0.1.1 255.255.255.0"},
						{"key":"security-level","security-level":"0"}
					]
				},
				{"key":"origin","origin":"no ip domain lookup"},
				{"key":"origin","origin":"multilink bundle-name authenticated"}


			]
		}
	)";

	const std::string expectDestDoc =
		R"(
		{
			"version":"15.1",
			"hostname":"device1",
			"interfaces":
			[
				{"interface":"g/0.1","ip adress":"127.0.0.1 255.255.255.0","security-level":"0"},
				{"interface":"g/1.1","ip adress":"127.0.1.1 255.255.255.0","security-level":"0"}
			],
			"childs":
			[
				{"key":"origin","origin":"no ip domain lookup"},
				{"key":"origin","origin":"multilink bundle-name authenticated"}
			]
		}
		)";


	DoTest(sourceDoc, expectDestDoc);
}