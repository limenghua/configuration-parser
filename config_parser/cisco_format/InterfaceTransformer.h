/*******************************************************************
*  Copyright(c) 2010-2017 Netbrain
*  All rights reserved.
*
*  文件名称: InterfaceTransformer.h
*  简要描述:
*
*  当前版本:
*  作者: limenghua
*  日期: 2017/05/07
*  说明:
*
******************************************************************/

#pragma once

#include "Transformer.h"

class InterfaceTransformer :public DefualtTransformer
{
public:
	Json::Value Transform(const Json::Value & input)override
	{
		Json::Value root;
		Json::Value item = _subTransformer.Transform(input);
		root["interfaces"].append(item);
		return root;
	}

private:
	DefualtTransformer _subTransformer;
};