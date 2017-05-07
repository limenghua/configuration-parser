#include <gtest/gtest.h>
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

TEST(JsonTest, Value)
{
	Json::Value root;
	root["name"] = "tom";
	root["age"] = 22;

	EXPECT_FALSE(root["name"].isNull());
	EXPECT_TRUE(root["name"].isString());

	EXPECT_EQ(root["name"].asString(), "tom");
	EXPECT_EQ(root["age"].asInt(), 22);
}

TEST(JsonTest, Reader)
{
	std::string strDoc = 
R"({
	"name":"tom",
	"age":22
})";

	Json::Value root;
	Json::Reader reader;

	bool ret = reader.parse(strDoc, root);

	EXPECT_TRUE(ret);

	EXPECT_FALSE(root["name"].isNull());
	EXPECT_TRUE(root["name"].isString());

	EXPECT_EQ(root["name"].asString(), "tom");
	EXPECT_EQ(root["age"].asInt(), 22);
}

TEST(JsonTest, Reader2)
{
	std::string strDoc =
		R"({
	"name":"tom",
	"age":22,
	"loveNum":[3,8,5,9]
})";

	Json::Value root;
	Json::Reader reader;

	bool ret = reader.parse(strDoc, root);

	EXPECT_TRUE(ret);

	EXPECT_FALSE(root["name"].isNull());
	EXPECT_TRUE(root["name"].isString());

	EXPECT_EQ(root["name"].asString(), "tom");
	EXPECT_EQ(root["age"].asInt(), 22);

	Json::Value nums = root["loveNum"];
	EXPECT_TRUE(nums.isArray());

	EXPECT_EQ(nums[0].asInt(), 3);
	EXPECT_EQ(nums[1].asInt(), 8);
	EXPECT_EQ(nums[2].asInt(), 5);
	EXPECT_EQ(nums[3].asInt(), 9);
}

TEST(JsonTest, ObjectCopyed)
{
	Json::Value root;

	Json::Value detail;

	detail["name"] = "tom";
	detail["age"] = 1;

	root["detail"] = detail;


	EXPECT_FALSE(root["detail"].isNull());
	EXPECT_TRUE(root["detail"].isObject());

	detail["age"] = 2;

	EXPECT_EQ(root["detail"]["age"].asInt(), 1);

}


TEST(JsonTest, Writer)
{
	Json::Value root;
	root["name"] = "tom";
	root["age"] = 22;

	Json::FastWriter writer;
	std::string strJson = writer.write(root);

	EXPECT_TRUE(!strJson.empty());

}