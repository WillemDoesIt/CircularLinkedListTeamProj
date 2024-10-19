#include "gtest/gtest.h"
#include "CircularLinkedList.h"
#include <string>


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PopBack, ThreeItems) {
    CS273::CircLinkedList<std::string> myList;
	myList.push_back("item1");
    myList.push_back("item2");
    myList.push_back("item3");
    myList.pop_back();
    EXPECT_EQ(myList.size(), 2);
    EXPECT_EQ(myList.front(), "item1");
    EXPECT_EQ(myList.back(), "item2");
    // TODO: once you have the iterator setup iterate through to make sure all works
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