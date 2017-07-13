/******************************************************************* 
 *  Copyright(c) 2010-2017 Nethead
 *  All rights reserved. 
 *   
 *  文件名称: ParserUtil.h
 *  简要描述: 
 *   
 *  当前版本: 
 *  作者: limenghua
 *  日期: 4/25/2017
 *  说明:  
 *
 ******************************************************************/
#pragma once

#include <string>
#include <vector>

/** 
* @brief :将一个Cisco configure命令行拆分为空格前缀和实际命令两部分
* @param :content [in] 需要拆分的原始数据，输入，只读 
* @param :prefix [out] 拆分后的前导空格（包括Table"\t"） 
* @param :cmd [out] 拆分后出去前导空格的剩余部分字符
*
* @example :
* 	const std::string content = "  no ip domain lookup";
*   std::string strPrefix;
*   std::string strCmd;
*   SplitPrefixSpaces(content, strPrefix, strCmd);
*   //result: strPrefix shoud be "  ",strCmd should be "no ip domain lookup"
*/
void SplitPrefixSpaces(const std::string & content, std::string & prefix, std::string & cmd);

/** 
* @brief 比较两个只包含空格类字符前缀串的大小，用于确定解析时语句的父子包含关系
* @param strSource 比较的源字符串
* @param strDes 比较的目的字符串
*
* @return 1：strSource包含strDest, -1:strDest包含strSource, 0:两个前缀完全相等
* @throw std::exeption ,when 两个前缀彼此不包含又不相等
* 
*/
int PrefixCompare(const std::string & strSource, const std::string & strDest);

/** 
* @brief 去掉注释文本，注释以!号开始，到换行符结束
* @param strContent ，输入文本 
*
* @return 去掉注释后的文本
* 
* @example:
*   string strRes = EraseCommentUseExclamatory("!this is comment");
*	assert(strRes == "");
*	strRes = EraseCommentUseExclamatory("version 15.2!this is comment");
*	assert(strRes == "version 15.2");
*	strRes = EraseCommentUseExclamatory("version 15.2");
*	assert(strRes == "version 15.2");
*/
std::string EraseCommentUseExclamatory(const std::string & strContent);

/** 
* @brief 去掉字符串前后导空格或tab
* @param str 输入字符串
*
* @return 去掉前后导空格后的字符串
* 
* 
*/
std::string Trim(const std::string & str);

/** 
* @brief 使用空格分割单词
* @param str 输入字符串
* @param words 分割后的输出单词.
*
*  
* 
*/
void SplitWords(const std::string & str, std::vector<std::string> & words);