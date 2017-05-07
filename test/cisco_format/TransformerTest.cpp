#include <gtest/gtest.h>
#include <json/json.h>
#include <iostream>
#include <string>
#include "Transformer.h"

#include "TestUtil.h"

TEST(TransformerTest, MergeInto_DefualtIsCopyAllPropertyIntoDest)
{
	Json::Value source;
	source["hostname"] = "device1";
	source["version"] = "15.2";

	DefualtTransformer t;
	Json::Value dest;
	t.MergeInto(source, dest);

	EXPECT_EQ(dest["hostname"].asString(), "device1");
	EXPECT_EQ(dest["version"].asString(), "15.2");
}

TEST(TransformerTest, MergeInto_IfPropertyExsistShouldIgnoredIt)
{
	Json::Value source;
	source["hostname"] = "device1";
	source["version"] = "15.2";

	DefualtTransformer t;
	Json::Value dest;
	dest["version"] = "14.0";

	t.MergeInto(source, dest);

	EXPECT_EQ(dest["hostname"].asString(), "device1");
	EXPECT_EQ(dest["version"].asString(), "14.0");
}

TEST(TransformerTest, MergeInto_IfExsistedPropertyIsArrayShouldAppendInto)
{
	const std::string sourceJson =
	R"({
		"hostname":"device1",
		"interfaces":
		[
			{"name":"g/0.1","ip adress":"192.168.0.1 255.255.255.0"}
		]
	})";

	const std::string destJson =
	R"({
		"interfaces":
		[
			{"name":"g/1.1","ip adress":"192.168.0.2 255.255.255.0"},
			{"name":"g/2.1","ip adress":"192.168.0.3 255.255.255.0"}
		]
	})";

	const std::string expectMegerdJson =
	R"({
		"hostname":"device1",
		"interfaces":
		[
			{"name":"g/1.1","ip adress":"192.168.0.2 255.255.255.0"},
			{"name":"g/2.1","ip adress":"192.168.0.3 255.255.255.0"},
			{"name":"g/0.1","ip adress":"192.168.0.1 255.255.255.0"}
		]
	})";

	Json::Value source = CreateJsonFromString(sourceJson);
	Json::Value dest = CreateJsonFromString(destJson);
	Json::Value expectMegerd = CreateJsonFromString(expectMegerdJson);

	DefualtTransformer t;
	t.MergeInto(source, dest);
	EXPECT_EQ(dest, expectMegerd);
}


TEST(TransformerTest, Tranformer_DefualtIsCopyAllPropertyIntoDest)
{
	Json::Value source;
	source["key"] = "hostname";
	source["hostname"] = "device1";

	DefualtTransformer t;
	
	Json::Value dest=  t.Transform(source);

	EXPECT_EQ(dest["hostname"].asString(), "device1");

}