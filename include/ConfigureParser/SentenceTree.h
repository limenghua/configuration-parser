/******************************************************************* 
 *  Copyright(c) 2010-2017 Nethead
 *  All rights reserved. 
 *   
 *  文件名称: SentenceTree.h
 *  简要描述: 
 *   
 *  当前版本: 
 *  作者: limenghua
 *  日期: 4/26/2017
 *  说明: Class CentenceTree 
 *
 ******************************************************************/
#pragma once
#include <string>
#include <vector>

class SentenceTree
{
public:
	typedef std::vector<SentenceTree> ChildsCollection;
	typedef ChildsCollection::iterator child_iterator;
	typedef ChildsCollection::const_iterator child_const_iterator;
public:
	
	SentenceTree() = default;

	SentenceTree(const std::string & value) :
		_sentence(value)
	{}

	std::string GetData()const
	{
		return _sentence;
	}

	void SetData(const std::string & data)
	{
		_sentence = data;
	}

	bool Empty()const
	{
		return _sentence.empty() && _childs.empty();
	}

	SentenceTree & AddChild(const std::string & data)
	{
		_childs.push_back(SentenceTree(data));
		return _childs.back();
	}

	child_iterator ChildBegin()
	{
		return _childs.begin();
	}
	child_iterator ChildEnd()
	{
		return _childs.end();
	}

	child_const_iterator ChildBegin()const
	{
		return _childs.cbegin();
	}

	child_const_iterator ChildEnd() const
	{
		return _childs.cend();
	}

	ChildsCollection & GetChilds()
	{
		return _childs;
	}

	const ChildsCollection & GetChilds()const
	{
		return _childs;
	}

	size_t GetChildCount()const
	{
		return _childs.size();
	}

	const SentenceTree & GetChild(size_t index)const
	{
		return _childs[index];
	}

	SentenceTree & GetChild(size_t index)
	{
		return _childs[index];
	}

private:
	std::string _sentence;
	ChildsCollection _childs;
};
