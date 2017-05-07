/******************************************************************* 
 *  Copyright(c) 2010-2017 Netbrain
 *  All rights reserved. 
 *   
 *  文件名称: ParserUtil.cpp
 *  简要描述: 
 *   
 *  当前版本: 
 *  作者: limenghua
 *  日期: 4/25/2017
 *  说明:  
 *
 ******************************************************************/

#include "ParserUtil.h"

static const char * SPACES_CHARS = " \t\n\r";

void SplitPrefixSpaces(const std::string & content, std::string & prefix, std::string & cmd)
{


	size_t pos = content.find_first_not_of(SPACES_CHARS);

	if (pos != content.npos)
	{
		prefix = content.substr(0, pos);
		cmd = content.substr(pos);
	}
	else
	{
		prefix = content;
		cmd = "";
	}

}

int PrefixCompare(const std::string & strSource, const std::string & strDest)
{
	size_t index = 0;
	while (index < strSource.size() && index < strDest.size())
	{
		if (strSource[index] != strDest[index])
		{
			throw std::exception("syntax error,prefix is not comparable");
		}
		index++;
	}
	if (strSource.size() > strDest.size())return 1;
	if (strSource.size() < strDest.size())return -1;
	return 0;
}

std::string EraseCommentUseExclamatory(const std::string & strContent)
{
	size_t pos = strContent.find('!');
	return strContent.substr(0, pos);
}

std::string Trim(const std::string & str)
{
	if (str.empty())return str;

	size_t startPos = str.find_first_not_of(SPACES_CHARS);
	if (startPos == str.npos)return "";

	size_t endPos = str.find_last_not_of(SPACES_CHARS);
	if (endPos == str.npos)return "";


	return str.substr(startPos, endPos - startPos+1);
}

void SplitWords(const std::string & str, std::vector<std::string> & words)
{
	const std::string regularExp = SPACES_CHARS;

	std::string input = Trim(str);
	int startPos = 0;
	int len = input.length();

	while (startPos < len)
	{
		int endPos = input.find_first_of(regularExp, startPos);
		if (endPos < 0)
		{
			std::string tmp = input.substr(startPos);
			words.push_back(tmp);
			break;
		}
		else
		{
			std::string tmp = input.substr(startPos, endPos - startPos);
			words.push_back(tmp);
		}
		startPos = input.find_first_not_of(regularExp,endPos + 1);

		if (startPos == input.npos)break;
	}
}