/*******************************************************************
*  Copyright(c) 2010-2017 Netbrain
*  All rights reserved.
*
*  文件名称: configure_parser.h
*  简要描述:
*
*  当前版本:
*  作者: limenghua
*  日期: 2017/05/07
*  说明:
*
******************************************************************/
#pragma once

#include <iostream>
#include "ConfigureParser/SentenceTree.h"

void ParseConfigToSentenceTree(std::istream & in, SentenceTree & tree);
void ParseConfigToSentenceTree(const std::string & strContent, SentenceTree & tree);


void ParseConfigToJson(std::istream & in, std::ostream & out);
void ParseConfigToJson(const std::string & strContent, std::string & strOutput);