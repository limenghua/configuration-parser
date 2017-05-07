#include <gtest/gtest.h>
#include "ConfigureParser/SentenceTree.h"



TEST(TreeTest, ConstructAnEmptyTree)
{
	SentenceTree t;
	EXPECT_TRUE(t.Empty());
}

TEST(TreeTest, ConstructWithValue)
{
	SentenceTree t("test string");
	EXPECT_FALSE(t.Empty());
	EXPECT_EQ(t.GetData(), "test string");
}

TEST(TreeTest, ConstructSetData)
{
	SentenceTree t;
	EXPECT_TRUE(t.Empty());
	
	t.SetData("test string");
	EXPECT_FALSE(t.Empty());
	EXPECT_EQ(t.GetData(), "test string");
}

TEST(TreeTest, AddChildShouldRetrunChildAdded)
{
	SentenceTree t("root");
	SentenceTree & child = t.AddChild("child");

	EXPECT_EQ(child.GetData(), "child");
}

TEST(TreeTest, GetChilds)
{
	SentenceTree t("root");
	t.AddChild("child0");
	t.AddChild("child1");
	t.AddChild("child2");

	auto childs = t.GetChilds();

	EXPECT_EQ(childs.size(), 3);
	EXPECT_EQ(childs.back().GetData(), "child2");

	EXPECT_EQ(t.GetChildCount(), 3);

	EXPECT_EQ(t.GetChild(0).GetData(), "child0");
	EXPECT_EQ(t.GetChild(1).GetData(), "child1");
	EXPECT_EQ(t.GetChild(2).GetData(), "child2");
}

