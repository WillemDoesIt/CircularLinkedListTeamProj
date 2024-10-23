#include "gtest/gtest.h"
#include "CircularLinkedList.h"
#include <string>


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Constructor, Copy) {
    CS273::CircLinkedList<std::string> myList;

    myList.push_back("item1");
    myList.push_back("item2");
    myList.push_back("item3");
    CS273::CircLinkedList<std::string> myList2(myList);

    EXPECT_EQ(myList.size(), 3);
    EXPECT_EQ(myList2.size(), 3);
}

TEST(Iterator, OneItem) {
    CS273::CircLinkedList<std::string> myList;
    myList.push_back("item1");
    CS273::CircLinkedList<std::string>::iterator it = myList.begin();
    EXPECT_EQ(*it, "item1");
    ++it;
    EXPECT_EQ(*it, "item1"); // doesn't advance
}

TEST(Iterator, ThreeItems) {
    CS273::CircLinkedList<std::string> myList;
    myList.push_back("item1");
    myList.push_back("item2");
    myList.push_back("item3");
    CS273::CircLinkedList<std::string>::iterator it = myList.begin();
    EXPECT_EQ(*it, "item1");
    ++it;
    EXPECT_EQ(*it, "item2");
    ++it;
    EXPECT_EQ(*it, "item3");
    ++it;
    EXPECT_EQ(*it, "item1"); // returns back to the start
}

TEST(PopBack, ThreeItems) {
    CS273::CircLinkedList<std::string> myList;
	myList.push_back("item1");
    myList.push_back("item2");
    myList.push_back("item3");
    myList.pop_back();
    EXPECT_EQ(myList.size(), 2);
    // iterate through to check values
    CS273::CircLinkedList<std::string>::iterator it = myList.begin();
	EXPECT_EQ(*it, "item1");
    ++it;
    EXPECT_EQ(*it, "item2");
    ++it;
    EXPECT_EQ(*it, "item1"); // returns back to the start
}

TEST(PopBack, OneItem) {
    CS273::CircLinkedList<std::string> myList;
    myList.push_back("item1");
    myList.pop_back();

    EXPECT_EQ(myList.empty(), 1);
}


TEST(PopBack, EmptyList) {
    CS273::CircLinkedList<std::string> myList;
    EXPECT_NO_THROW(myList.pop_back());
}

TEST(PopFront, ThreeItems) {
    CS273::CircLinkedList<std::string> myList;
	myList.push_back("item1");
    myList.push_back("item2");
    myList.push_back("item3");
    myList.pop_front();
    EXPECT_EQ(myList.size(), 2);
    EXPECT_EQ(myList.front(), "item2");
    EXPECT_EQ(myList.back(), "item3");
}

TEST(PopFront, OneItem) {
    CS273::CircLinkedList<std::string> myList;
	myList.push_back("item1");
    myList.pop_front();
    EXPECT_EQ(myList.empty(), 1);
}

TEST(PopFront, EmptyList) {
    CS273::CircLinkedList<std::string> myList;
    EXPECT_NO_THROW(myList.pop_front());
}

TEST(PushFront, ThreeItems) {
    CS273::CircLinkedList<std::string> myList;
    myList.push_back("item1");
    myList.push_back("item2");
    myList.push_back("item3");

    myList.push_front("newItem");

    EXPECT_EQ(myList.size(), 4);
    EXPECT_EQ(myList.front(), "newItem");
    EXPECT_EQ(myList.back(), "item3");
}

TEST(PushFront, MultiplePushes) {
    CS273::CircLinkedList<std::string> myList;
    myList.push_front("item1");
    myList.push_front("item2");
    myList.push_front("item3");

    EXPECT_EQ(myList.size(), 3);
    EXPECT_EQ(myList.front(), "item3");
    EXPECT_EQ(myList.back(), "item1");
}

TEST(PushFront, OneItem) {
    CS273::CircLinkedList<std::string> myList;
    myList.push_back("item1");

    myList.push_front("newItem");

    EXPECT_EQ(myList.size(), 2);
    EXPECT_EQ(myList.front(), "newItem");
    EXPECT_EQ(myList.back(), "item1");
}


TEST(PushFront, EmptyList) {
    CS273::CircLinkedList<std::string> myList;
    myList.push_front("item1");

    EXPECT_EQ(myList.size(), 1);
    EXPECT_EQ(myList.front(), "item1");
    EXPECT_EQ(myList.back(), "item1");
}