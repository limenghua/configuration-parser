#include "ParserUtil.h"

#include <gtest/gtest.h>
#include <string>

TEST(SplitPrefixSpaces, EmptyContentSplteTwoEmptyString)
{
	const std::string content = "";

	std::string strPrefix;
	std::string strCmd;

	SplitPrefixSpaces(content, strPrefix, strCmd);

	EXPECT_EQ(strPrefix, "");
	EXPECT_EQ(strCmd, "");
}

TEST(SplitPrefixSpaces, OnlyPrefixSpacesCommandShoudEmpty)
{
	const std::string content = " ";

	std::string strPrefix;
	std::string strCmd;

	SplitPrefixSpaces(content, strPrefix, strCmd);

	EXPECT_EQ(strPrefix, " ");
	EXPECT_EQ(strCmd, "");
}

TEST(SplitPrefixSpaces, HasOnlyOneSpaces)
{
	const std::string content = " no ip domain lookup";

	std::string strPrefix;
	std::string strCmd;

	SplitPrefixSpaces(content, strPrefix, strCmd);

	EXPECT_EQ(strPrefix, " ");
	EXPECT_EQ(strCmd, "no ip domain lookup");
}

TEST(SplitPrefixSpaces, NoHasMoreThanOneSpaces)
{
	std::string strPrefix;
	std::string strCmd;

	//prefix has two spaces
	SplitPrefixSpaces("  no ip domain lookup", strPrefix, strCmd);

	EXPECT_EQ(strPrefix, "  ");
	EXPECT_EQ(strCmd, "no ip domain lookup");

	//prefix has three spaces
	SplitPrefixSpaces("   another command example", strPrefix, strCmd);
	EXPECT_EQ(strPrefix, "   ");
	EXPECT_EQ(strCmd, "another command example");

	//prefix has many spaces
	const std::string strManySpaces =
		"                                                                                                        "
		"                                                                                                        "
		"                                                                                                        "
		"                                                                                                        "
		"                                                                                                        "
		"                                                                                                        "
		"                                                                                                        "
		"                                                                                                        ";
	std::string content = strManySpaces + "many spaces command example";
	SplitPrefixSpaces(content, strPrefix, strCmd);
	EXPECT_EQ(strPrefix, strManySpaces);
	EXPECT_EQ(strCmd, "many spaces command example");

}

TEST(SplitPrefixSpaces, NoHasSomeSpacesAndTable)
{
	const std::string content = "   \tno ip domain lookup";

	std::string strPrefix;
	std::string strCmd;

	SplitPrefixSpaces(content, strPrefix, strCmd);

	EXPECT_EQ(strPrefix, "   \t");
	EXPECT_EQ(strCmd, "no ip domain lookup");
}

TEST(SplitPrefixSpaces, SomeComplexPrefix)
{
	std::string strPrefix;
	std::string strCmd;

	const std::string strManySpaces =
		"       \t  \t      \t             \t                                 ";

	std::string content = strManySpaces + "some complex command example";
	SplitPrefixSpaces(content, strPrefix, strCmd);
	EXPECT_EQ(strPrefix, strManySpaces);
	EXPECT_EQ(strCmd, "some complex command example");
}