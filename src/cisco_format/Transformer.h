/*******************************************************************
*  Copyright(c) 2010-2017 Netbrain
*  All rights reserved.
*
*  文件名称: Transformer.h
*  简要描述:
*
*  当前版本:
*  作者: limenghua
*  日期: 2017/05/07
*  说明:
*
******************************************************************/
#pragma once

#include <json/value.h>

/************************************************************************/
/* json 格式的变换
 * example:
 *	json input :
 *	{
 *		"key":"root",
 *		"childs":
 *		[
 *			{"key":"version","version":"15.1"},
 *			{"key":"hostname","hostname":"device1"}
 *		]
 *	}
 *
 *	json outpu:
 *	{
 *		"version":"15.1",
 *		"hostname":"device1"
 *	}
*/
/************************************************************************/
class ITransformer
{
public:
	typedef ITransformer * ITransformerPtr;
	virtual ~ITransformer()
	{
	}
	virtual Json::Value Transform(const Json::Value & input) = 0;
};

class DefualtTransformer :public ITransformer
{
public:
	virtual Json::Value Transform(const Json::Value & input)override;

	virtual void MergeInto(const Json::Value & source, Json::Value & dest);

	virtual Json::Value TransformSelf(const Json::Value & input);

	virtual ITransformerPtr GetSubTransformer(const std::string & key)
	{
		return this;
	}
};

class OriginTransformer :public ITransformer
{
public:
	virtual Json::Value Transform(const Json::Value & input)
	{
		Json::Value root;
		root["childs"].append(input);
		return root;
	}
};