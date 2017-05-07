#include <gtest/gtest.h>
#include "ParserUtil.h"

using namespace std;

TEST(SplitWordsTest, EmptyString)
{
	vector<string> words;
	SplitWords("", words);
	EXPECT_TRUE(words.empty());
}

TEST(SplitWordsTest, OneWords)
{
	vector<string> words;
	SplitWords("one", words);
	EXPECT_FALSE(words.empty());
	EXPECT_EQ(words[0], "one");
}

TEST(SplitWordsTest, SomeWords)
{
	vector<string> words;
	SplitWords("one two \tthree  four", words);

	EXPECT_EQ(words.size(), 4);
	EXPECT_EQ(words[0], "one");
	EXPECT_EQ(words[1], "two");
	EXPECT_EQ(words[2], "three");
	EXPECT_EQ(words[3], "four");
}