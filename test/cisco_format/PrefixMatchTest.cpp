#include <gtest/gtest.h>
#include "PrefixMatcher.h"


TEST(PrefixMatcher, ConstructWithString)
{
	PrefixMatcher matcher("hostname");
	EXPECT_EQ(matcher.GetPrefixKey(), "hostname");
}

TEST(PrefixMatcher, PrefixNotEqualMatchShouldFaild)
{
	PrefixMatcher matcher("hostname");
	EXPECT_FALSE(matcher.Match("Myhostname hello"));
}

TEST(PrefixMatcher, MatchPrefixKeyString)
{
	PrefixMatcher matcher("hostname");
	EXPECT_TRUE(matcher.Match("hostname hello"));
	EXPECT_EQ(matcher.GetSpared(), "hello");
	EXPECT_FALSE(matcher.IsStartWithNo());
}

TEST(PrefixMatcher, MultiSpaceShouldBeIgnored)
{
	PrefixMatcher matcher("ip address");
	EXPECT_TRUE(matcher.Match("ip   address 127.0.0.1"));
	EXPECT_EQ(matcher.GetSpared(), "127.0.0.1");
	EXPECT_FALSE(matcher.IsStartWithNo());
}

TEST(PrefixMatcher, CaseShouldBeIgnored)
{
	PrefixMatcher matcher("ip Address");
	EXPECT_TRUE(matcher.Match("Ip   address 127.0.0.1"));
	EXPECT_EQ(matcher.GetSpared(), "127.0.0.1");
	EXPECT_FALSE(matcher.IsStartWithNo());
}

TEST(PrefixMatcher, CanMatchWordsStartWithNo)
{
	PrefixMatcher matcher("ip address");
	EXPECT_TRUE(matcher.Match("no ip address"));
	EXPECT_EQ(matcher.GetSpared(), "");
	EXPECT_TRUE(matcher.IsStartWithNo());
}