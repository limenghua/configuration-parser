/*******************************************************************
*  Copyright(c) 2010-2017 Netbrain
*  All rights reserved.
*
*  文件名称: TestUtil.h
*  简要描述:
*
*  当前版本:
*  作者: limenghua
*  日期: 2017/05/07
*  说明:
*
******************************************************************/
#pragma once

#include <json/json.h>

inline Json::Value CreateJsonFromString(const std::string & strJson)
{
	Json::Value value;
	Json::Reader reader;
	reader.parse(strJson, value);
	return value;
}

inline std::string Stringfy(const Json::Value & value)
{
	Json::FastWriter writer;
	return writer.write(value);
}