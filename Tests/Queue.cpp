//
// Created by antoine on 22/12/23.
//

#include <gtest/gtest.h>
#include <iostream>
#include "Queue/QueueImplem.hpp"

using namespace express_cpp;
TEST(Queue, basic)
{
    QueueImplem<int> queue;
    queue.Push(1);
    queue.Push(2);
    EXPECT_EQ(queue.Pop(), 1);
    EXPECT_EQ(queue.IsEmpty(), false);
    EXPECT_EQ(queue.Pop(), 2);
    EXPECT_EQ(queue.IsEmpty(), true);
}

TEST(Queue, should_throw)
{
    QueueImplem<int> queue;
    queue.Push(1);
    queue.Push(2);
    EXPECT_EQ(*queue.Pop(), 1);
    EXPECT_EQ(queue.IsEmpty(), false);
    EXPECT_EQ(*queue.Pop(), 2);
    EXPECT_EQ(queue.IsEmpty(), true);
    EXPECT_EQ(queue.Pop().has_value(), false);
}

TEST(Queue, initializer_list_constructor)
{
    QueueImplem<int> queue{1, 2};
    EXPECT_EQ(queue.Pop(), 1);
    EXPECT_EQ(queue.IsEmpty(), false);
    EXPECT_EQ(queue.Pop(), 2);
    EXPECT_EQ(queue.IsEmpty(), true);
}
