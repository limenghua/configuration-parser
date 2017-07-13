/*******************************************************************
*  Copyright(c) 2010-2017 Nethead
*  All rights reserved.
*
*  文件名称: PrefixMatcher.h
*  简要描述:
*
*  当前版本:
*  作者: limenghua
*  日期: 2017/05/26
*  说明:
*
******************************************************************/
#pragma once
#include <string>
#include <ctype.h>

class PrefixMatcher
{
public:
	PrefixMatcher(const std::string & prefix) :
		_prefixKey(prefix),
		_isStartWithNo(false)
	{
	}
	const std::string & GetPrefixKey()
	{
		return _prefixKey;
	}
	bool Match(const std::string str)
	{
		_isStartWithNo = false;
		size_t i = 0;
		size_t j = 0;
		if (str.find("no") == 0)
		{
			_isStartWithNo = true;
			j += 2;
			while (j < str.size() && isspace(str[j]))j++;
		}

		while (i < _prefixKey.size() && j < str.size())
		{
			if (tolower(_prefixKey[i]) != tolower(str[j]))return false;

			if (!isspace(_prefixKey[i]))
			{
				i++;
				j++;
				continue;
			}
			while (i < _prefixKey.size() && isspace(_prefixKey[i]))i++;
			while (j < str.size() && isspace(str[j]))j++;
		}
		if (i < _prefixKey.size())return false;

		while (j < str.size() && isspace(str[j]))j++;
		_sparedStr = str.substr(j);
		return true;
	}

	std::string GetSpared()
	{
		return _sparedStr;
	}

	bool IsStartWithNo()
	{
		return _isStartWithNo;
	}

private:
	std::string _prefixKey;
	std::string _sparedStr;
	bool _isStartWithNo;
};
