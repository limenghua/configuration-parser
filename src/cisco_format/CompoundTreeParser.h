/******************************************************************* 
 *  Copyright(c) 2010-2017 Netbrain
 *  All rights reserved. 
 *   
 *  文件名称: CompoundTreeParser.h
 *  简要描述: 
 *   
 *  当前版本: 
 *  作者: limenghua
 *  日期: 4/27/2017
 *  说明:  
 *
 ******************************************************************/
#pragma once
#include "ParserUtil.h"
#include "TreeParser.h"
#include <list>

class CompoundTreeParser :public TreeParser
{
public:
	virtual Json::Value Parse(const SentenceTree & tree) override
	{
		Json::Value root = ParserSentence(Trim(tree.GetData()));

		if (_subParsers.empty())return root;

		Json::Value childs;
		const auto & subTrees = tree.GetChilds();
		for (auto & subTree : subTrees)
		{
			ITreeParserPtr subParser = GetBestSubParser(subTree.GetData());
			if (subParser == nullptr)
			{
				continue;
			}

			Json::Value value = subParser->Parse(subTree);
			childs.append(value);
		}

		if (childs.isArray())
		{
			root["childs"] = childs;
		}

		return root;
	}

	void AddSubParser(ITreeParserPtr subParser)
	{
		_subParsers.push_back(subParser);
	}

	ITreeParserPtr GetBestSubParser(const std::string & strSentence)
	{
		int maxScore = -1;
		ITreeParserPtr parser = nullptr;
		for (auto p : _subParsers)
		{
			int score = p->ScoreMatchSentence(strSentence);
			if (score > maxScore)
			{
				maxScore = score;
				parser = p;
			}
		}
		return parser;
	}

protected:
	std::list<ITreeParserPtr> _subParsers;
};