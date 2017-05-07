#include <gtest/gtest.h>
#include <sstream>
#include "SentenceTree.h"
#include "TreeParser.h"
#include <list>

TEST(ParseConfigToSentenceTreeTest, OnlyOnceSentenceShouldParseOneChild)
{
	const std::string strConfigContent = "version 15.2";
	std::stringstream ss(strConfigContent);

	SentenceTree tree;

	ParseConfigToSentenceTree(ss, tree);

	EXPECT_FALSE(tree.Empty());
	SentenceTree::ChildsCollection & childs = tree.GetChilds();
	EXPECT_EQ(childs.size(), 1);

	SentenceTree & firstChild = childs.front();
	EXPECT_EQ(firstChild.GetData(), "version 15.2");
}

TEST(ParseConfigToSentenceTreeTest, TwoSentenceShouldParseTwoChilds)
{
	
	std::stringstream ss;
	ss << "version 15.2"<<std::endl;
	ss << "hostname example";

	SentenceTree tree;

	ParseConfigToSentenceTree(ss, tree);

	EXPECT_FALSE(tree.Empty());
	SentenceTree::ChildsCollection & childs = tree.GetChilds();
	EXPECT_EQ(childs.size(), 2);

	SentenceTree & firstChild = childs.front();
	EXPECT_EQ(firstChild.GetData(), "version 15.2");
	SentenceTree & secondtChild = childs.back();
	EXPECT_EQ(secondtChild.GetData(), "hostname example");
}

TEST(ParseConfigToSentenceTreeTest, MoreSentenceShouldParseSameMoreChilds)
{
	std::list<std::string> sentencese =
	{
		"Building configuration...",
		"version 15.2",
		"service timestamps debug datetime msec",
		"hostname example",
		"boot-start-marker",
		"boot-end-marker",
	};

	std::stringstream ss;
	for (auto & value : sentencese)
	{
		ss << value << std::endl;
	}

	SentenceTree tree;

	ParseConfigToSentenceTree(ss, tree);

	EXPECT_FALSE(tree.Empty());
	SentenceTree::ChildsCollection & childs = tree.GetChilds();
	EXPECT_EQ(childs.size(), sentencese.size());

	auto childsIter = tree.ChildBegin();
	for (auto & value : sentencese)
	{
		EXPECT_TRUE(childsIter != tree.ChildEnd());
		EXPECT_EQ(childsIter->GetData(), value);

		childsIter++;
	}
}

TEST(ParseConfigToSentenceTreeTest, NestingSentencesShouldParseNestingTree)
{
	const std::string strSentences =
		"interface Ethernet0/0\n"
		" ip address 158.4.0.170 255.255.255.252";
		//" ip access-group 1 in"
		//" ip access-group R3toR1 out"

	std::stringstream ss(strSentences);

	SentenceTree tree;
	ParseConfigToSentenceTree(ss, tree);

	EXPECT_FALSE(tree.Empty());
	SentenceTree::ChildsCollection & childs = tree.GetChilds();
	EXPECT_EQ(childs.size(), 1);

	SentenceTree & child = childs.front();
	EXPECT_EQ(child.GetData(), "interface Ethernet0/0");

	SentenceTree::ChildsCollection & grandSons = child.GetChilds();
	EXPECT_EQ(grandSons.size(), 1);

}

TEST(ParseConfigToSentenceTreeTest, NestingSentencesShouldParseNestingTree2)
{
	const std::string strSentences =
		"interface Ethernet0/0\n"
		" ip address 158.4.0.170 255.255.255.252\n"
		" ip access-group 1 in\n"
		" ip access-group R3toR1 out";

	std::stringstream ss(strSentences);

	SentenceTree tree;
	ParseConfigToSentenceTree(ss, tree);

	EXPECT_FALSE(tree.Empty());
	SentenceTree::ChildsCollection & childs = tree.GetChilds();
	EXPECT_EQ(childs.size(), 1);

	SentenceTree & child = childs.front();
	EXPECT_EQ(child.GetData(), "interface Ethernet0/0");

	SentenceTree::ChildsCollection & grandSons = child.GetChilds();
	EXPECT_EQ(grandSons.size(), 3);

}

TEST(ParseConfigToSentenceTreeTest, NestingSentencesShouldParseNestingTree3)
{
	const std::string strSentences =
		R"(
interface Ethernet0/0
 ip address 158.4.0.170 255.255.255.252
 ip access-group 1 in
 ip access-group R3toR1 out
)";

	std::stringstream ss(strSentences);

	SentenceTree tree;
	ParseConfigToSentenceTree(ss, tree);

	EXPECT_FALSE(tree.Empty());
	SentenceTree::ChildsCollection & childs = tree.GetChilds();
	EXPECT_EQ(childs.size(), 1);

	SentenceTree & child = childs.front();
	EXPECT_EQ(child.GetData(), "interface Ethernet0/0");

	SentenceTree::ChildsCollection & grandSons = child.GetChilds();
	EXPECT_EQ(grandSons.size(), 3);

	std::list<std::string> sentencese =
	{
		"ip address 158.4.0.170 255.255.255.252",
		"ip access-group 1 in",
		"ip access-group R3toR1 out"
	};

	auto treeIter = grandSons.begin();
	for (auto & item : sentencese)
	{
		EXPECT_EQ(treeIter->GetData(), item);
		treeIter++;
	}
}

TEST(ParseConfigToSentenceTreeTest, EmptyLineShouldIgnored)
{
	const std::string strSentences =
R"(
interface Ethernet0/0

 ip address 158.4.0.170 255.255.255.252
 ip access-group 1 in


 ip access-group R3toR1 out
)";

	std::stringstream ss(strSentences);

	SentenceTree tree;
	ParseConfigToSentenceTree(ss, tree);

	EXPECT_FALSE(tree.Empty());
	SentenceTree::ChildsCollection & childs = tree.GetChilds();
	EXPECT_EQ(childs.size(), 1);

	SentenceTree & child = childs.front();
	EXPECT_EQ(child.GetData(), "interface Ethernet0/0");

	SentenceTree::ChildsCollection & grandSons = child.GetChilds();
	EXPECT_EQ(grandSons.size(), 3);

	std::list<std::string> sentencese =
	{
		"ip address 158.4.0.170 255.255.255.252",
		"ip access-group 1 in",
		"ip access-group R3toR1 out"
	};

	auto treeIter = grandSons.begin();
	for (auto & item : sentencese)
	{
		EXPECT_EQ(treeIter->GetData(), item);
		treeIter++;
	}
}

TEST(ParseConfigToSentenceTreeTest, CommentedCharacterShouldIgnored)
{
	const std::string strSentences =
		R"(
interface Ethernet0/0
 ip address 158.4.0.170 255.255.255.252
 ip access-group 1 in
 !this is a coment
 ip access-group R3toR1 out
)";

	std::stringstream ss(strSentences);

	SentenceTree tree;
	ParseConfigToSentenceTree(ss, tree);

	EXPECT_FALSE(tree.Empty());
	SentenceTree::ChildsCollection & childs = tree.GetChilds();
	EXPECT_EQ(childs.size(), 1);

	SentenceTree & child = childs.front();
	EXPECT_EQ(child.GetData(), "interface Ethernet0/0");

	SentenceTree::ChildsCollection & grandSons = child.GetChilds();
	EXPECT_EQ(grandSons.size(), 3);

	std::list<std::string> sentencese =
	{
		"ip address 158.4.0.170 255.255.255.252",
		"ip access-group 1 in",
		"ip access-group R3toR1 out"
	};

	auto treeIter = grandSons.begin();
	for (auto & item : sentencese)
	{
		EXPECT_EQ(treeIter->GetData(), item);
		treeIter++;
	}
}

TEST(ParseConfigToSentenceTreeTest, TestSomeComplexCase)
{
	const std::string strSentences =
		R"(
version 15.2
hostname example
interface Ethernet0/0
 ip address 158.4.0.170 255.255.255.252
 ip access-group 1 in
 ip access-group R3toR1 out
interface Ethernet0/2
 no ip address
 shutdown
)";

	std::stringstream ss(strSentences);

	SentenceTree tree;
	ParseConfigToSentenceTree(ss, tree);

	EXPECT_EQ(tree.GetChildCount(), 4);

	EXPECT_EQ(tree.GetChild(0).GetData(), "version 15.2");
	EXPECT_EQ(tree.GetChild(1).GetData(), "hostname example");
	EXPECT_EQ(tree.GetChild(2).GetData(), "interface Ethernet0/0");
	EXPECT_EQ(tree.GetChild(3).GetData(), "interface Ethernet0/2");

	SentenceTree & interface1 = tree.GetChild(2);
	SentenceTree & interface2 = tree.GetChild(3);

	EXPECT_EQ(interface1.GetChildCount(), 3);
	EXPECT_EQ(interface2.GetChildCount(), 2);

	EXPECT_EQ(interface1.GetChild(0).GetData(), "ip address 158.4.0.170 255.255.255.252");
	EXPECT_EQ(interface1.GetChild(1).GetData(), "ip access-group 1 in");
	EXPECT_EQ(interface1.GetChild(2).GetData(), "ip access-group R3toR1 out");

	EXPECT_EQ(interface2.GetChild(0).GetData(), "no ip address");
	EXPECT_EQ(interface2.GetChild(1).GetData(), "shutdown");
}