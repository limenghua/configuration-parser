/******************************************************************* 
 *  Copyright(c) 2010-2017 Netbrain
 *  All rights reserved. 
 *   
 *  文件名称: ConfigureParser.h
 *  简要描述: 
 *   
 *  当前版本: 
 *  作者: limenghua
 *  日期: 4/26/2017
 *  说明:  
 *
 ******************************************************************/
#pragma once

#include "ParserUtil.h"
#include "ConfigureParser/SentenceTree.h"
#include <json/value.h>

/*
 *	从已分析完成的语句树SentenceTree中解析出Json格式数据
 */
class ITreeParser
{
public:
	typedef ITreeParser* ITreeParserPtr;
	/** 
	 * @brief 解析接口
	 * @param const SentenceTree & tree，[in],语句树，确切说是从Config文件中以缩进为标准解析出的树状包含结构
	 *
	 * @return 解析结果，JSon格式
	 * @exeption 格式错误会抛出std::exeption
	 *			
	 */
	virtual Json::Value Parse(const SentenceTree & tree) = 0;
	/**
	* @brief 语句与分析器匹配度检测，用于判断该对象是否适合解析该SentenceTree，用于在解析过程中筛选最合适的解析器，一般返回匹配到的关键字字符数量。
	* @param const std::string & strSentence，[in],待解析的语句，一般是SentenceTree的Data数据。
	*
	* @return int 匹配度，一般大于等于零认为可以用来解析，负值应该直接pass掉。
	*
	*/
	virtual int  ScoreMatchSentence(const std::string & strSentence) = 0;
	virtual ~ITreeParser(){};
};

class TreeParser :public ITreeParser
{
public:
	virtual Json::Value ParserSentence(const std::string & strSentence) = 0;

	virtual Json::Value Parse(const SentenceTree & tree) override
	{
		return ParserSentence(Trim(tree.GetData()));
	}
};

