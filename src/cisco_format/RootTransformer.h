/*******************************************************************
*  Copyright(c) 2010-2017 Nethead
*  All rights reserved.
*
*  文件名称: RootTransformer.h
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
#include "InterfaceTransformer.h"
#include <map>


class RootTransformer :public CompoundTransformer
{
public:
	RootTransformer()
	{
		AddSubTransformer("origin", new OriginTransformer());
		AddSubTransformer("interface", new InterfaceTransformer());
	}

	virtual Json::Value TransformSelf(const Json::Value & input)override
	{
		return Json::Value();
	}

	virtual ITransformerPtr GetDefualtTransformer()override
	{
		return &_subTransformsDefualt;
	}

private:
	DefualtTransformer _subTransformsDefualt;
};
