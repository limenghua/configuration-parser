#include "ParserUtil.h"

#include <gtest/gtest.h>
#include <exception>


TEST(PrefixCompare, SamePrefixIsEqual)
{
	EXPECT_EQ(PrefixCompare("", ""), 0);
	EXPECT_EQ(PrefixCompare(" ", " "), 0);
}

TEST(PrefixCompare, TheLongerPrefixIsBigger)
{
	EXPECT_EQ(PrefixCompare(" ", ""), 1);
	EXPECT_EQ(PrefixCompare("", " "), -1);

	EXPECT_EQ(PrefixCompare("    ", "  "), 1);
	EXPECT_EQ(PrefixCompare("", "    "), -1);

	EXPECT_EQ(PrefixCompare("  \t", "  "), 1);
	EXPECT_EQ(PrefixCompare("\t   ", "\t    "), -1);
}

TEST(PrefixCompareTest, TheLongestSubPrefixNotEqualShouldThrow)
{
	EXPECT_THROW(PrefixCompare("\t ", " "),std::exception);
	EXPECT_THROW(PrefixCompare(" \t ", "\t "), std::exception);
}