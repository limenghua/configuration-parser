/******************************************************************* 
 *  Copyright(c) 2010-2017 Nethead
 *  All rights reserved. 
 *   
 *  文件名称: InterfaceTreeParser.h
 *  简要描述: 
 *   
 *  当前版本: 
 *  作者: limenghua
 *  日期: 5/2/2017
 *  说明: 解析configure中interface数据段
 *	Example：
 *
 *	!
 *	interface Serial1/1
 *		ip address 158.4.255.66 255.255.255.252
 *		serial restart-delay 0
 *	!
 ******************************************************************/
#pragma once

#include "SimpleKeyValueParser.h"

class InterfaceTreeParser :public SimpleKeyValueTreeParser
{
public:
	InterfaceTreeParser() :
		SimpleKeyValueTreeParser("interface")
	{
		AddSubParser(new SimpleKeyValueTreeParser("ip address"));
		AddSubParser(new SimpleKeyValueTreeParser("serial restart-delay"));
		AddSubParser(new SimpleKeyValueTreeParser("security-level"));
		AddSubParser(new SimpleKeyValueTreeParser("nameif"));
		AddSubParser(new SimpleKeyValueTreeParser("management-only","true"));
		AddSubParser(new SimpleKeyValueTreeParser("encapsulation"));
		AddSubParser(new SimpleKeyValueTreeParser("shutdown", "true"));
	}

	~InterfaceTreeParser()
	{
		for (auto & parser : _subParsers)
		{
			delete parser;
		}
		_subParsers.clear();
	}

};