/******************************************************************* 
 *  Copyright(c) 2010-2017 Nethead
 *  All rights reserved. 
 *   
 *  文件名称: RootTreeParser.h
 *  简要描述: 
 *   
 *  当前版本: 
 *  作者: limenghua
 *  日期: 5/3/2017
 *  说明:  
 *
 ******************************************************************/

#include "SimpleKeyValueParser.h"
#include "InterfaceTreeParser.h"
#include "CompoundTreeParser.h"
#include "DefaultTreeParser.h"

class RootTreeParser :public CompoundTreeParser
{
public:
	RootTreeParser()
	{
		AddSubParser(new InterfaceTreeParser());
		AddSubParser(new SimpleKeyValueTreeParser("version"));
		AddSubParser(new SimpleKeyValueTreeParser("hostname"));
		AddSubParser(new DefaultTreeParser());
	}
	~RootTreeParser()
	{
		for (auto & parser : _subParsers)
		{
			delete parser;
		}
		_subParsers.clear();
	}
	Json::Value ParserSentence(const std::string & strSentence)override
	{
		Json::Value root;
		root["key"] = "root";
		return root;
	}

	int ScoreMatchSentence(const std::string & strSentence)
	{
		if (strSentence.empty())return 0;
		return -1;
	}
};