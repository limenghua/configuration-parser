#include <gtest/gtest.h>
#include "ParserUtil.h"

TEST(EraseCommentUseExclamatory, EmptyStringShuldRetrunEmptyString)
{
	EXPECT_EQ(EraseCommentUseExclamatory(""), "");
}

TEST(EraseCommentUseExclamatory, NoCommentCharShuldRetrunSameString)
{
	EXPECT_EQ(EraseCommentUseExclamatory("version 15.2"), "version 15.2");
}

TEST(EraseCommentUseExclamatory, BeginWithCommentCharShoudReturnEmptyString)
{
	const std::string strContent = "!version 15.2";

	std::string strRes = EraseCommentUseExclamatory(strContent);

	EXPECT_EQ(strRes, "");
}

TEST(EraseCommentUseExclamatory, MiddleWithCommentCharShoudReturnHeaderString)
{
	const std::string strContent = "version 15.2!this is comment";

	std::string strRes = EraseCommentUseExclamatory(strContent);

	EXPECT_EQ(strRes, "version 15.2");
}