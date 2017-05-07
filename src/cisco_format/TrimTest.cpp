#include <gtest/gtest.h>
#include <string>
#include "ParserUtil.h"

TEST(TrimTest, EmptyStringShoudReturnEmpty)
{
	const std::string str = "";
	EXPECT_TRUE(Trim(str).empty());
}

TEST(TrimTest, NoSpaceShoudReturnSameString)
{
	const std::string str = "hello world";
	EXPECT_EQ(Trim(str), str);
}

TEST(TrimTest, SpaceBeforeShoudReturnTrimedString)
{
	EXPECT_EQ(Trim("   hello world"), "hello world");
	EXPECT_EQ(Trim("\thello world"), "hello world");
	EXPECT_EQ(Trim("\t hello world"), "hello world");
	EXPECT_EQ(Trim(" \thello world"), "hello world");
	EXPECT_EQ(Trim(" \t hello world"), "hello world");
}

TEST(TrimTest, OnlySpaceShoudReturnEmptyString)
{
	EXPECT_EQ(Trim("  "), "");
	EXPECT_EQ(Trim(" \t "), "");
}

TEST(TrimTest, ShoudReturnTrimedString)
{
	EXPECT_EQ(Trim("hello world "), "hello world");
	EXPECT_EQ(Trim(" hello world "), "hello world");
	EXPECT_EQ(Trim("\t hello world \t"), "hello world");
	EXPECT_EQ(Trim(" \t hello world \t "), "hello world");
}