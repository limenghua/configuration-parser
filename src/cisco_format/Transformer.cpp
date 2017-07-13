/*******************************************************************
*  Copyright(c) 2010-2017 Nethead
*  All rights reserved.
*
*  文件名称: Transformer.cpp
*  简要描述:
*
*  当前版本:
*  作者: limenghua
*  日期: 2017/05/07
*  说明:
*
******************************************************************/

#include "Transformer.h"

Json::Value DefualtTransformer::Transform(const Json::Value & input)
{
	Json::Value root = TransformSelf(input);
	if (input.isMember("childs") && input["childs"].isArray())
	{
		for (auto & item : input["childs"])
		{
			std::string strSubKey = item["key"].asString();
			ITransformerPtr subTransformer = GetSubTransformer(strSubKey);
			if (subTransformer)
			{
				Json::Value value = subTransformer->Transform(item);
				MergeInto(value, root);
			}
		}
	}

	return root;
}

void DefualtTransformer::MergeInto(const Json::Value & source, Json::Value & dest)
{
	Json::Value::Members members = source.getMemberNames();
	for (auto key : members)
	{
		if (!dest.isMember(key))
		{
			dest[key] = source[key];
		}
		else if (dest[key].isArray() && source[key].isArray())
		{
			for (auto & item : source[key])
			{
				dest[key].append(item);
			}
		}
	}
}

Json::Value DefualtTransformer::TransformSelf(const Json::Value & input)
{
	Json::Value value;
	std::string strKey = input["key"].asString();
	value[strKey] = input[strKey];
	return value;
}