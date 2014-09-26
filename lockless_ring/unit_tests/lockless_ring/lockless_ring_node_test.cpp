/*
 * lockless_ring_test.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: sgao
 */


#include <gtest/gtest.h>

#include <cinttypes>

#include <node.h>

TEST(ring_node, init)
{
	sg::Node<int32_t> node;
    EXPECT_TRUE(node.prev() == NULL);
    EXPECT_TRUE(node.next() == NULL);
    EXPECT_TRUE(node.data() == 0);
}

TEST(ring_node, append_null)
{
	sg::Node<int32_t> node;

	node.append(NULL);
    EXPECT_TRUE(node.prev() == NULL);
    EXPECT_TRUE(node.next() == NULL);
    EXPECT_TRUE(node.data() == 0);
}

TEST(ring_node, append_node)
{
	sg::Node<int32_t> node1;
	sg::Node<int32_t> node2;

	node2.append(&node1);
    EXPECT_TRUE(node1.prev() == NULL);
    EXPECT_TRUE(node1.next() == &node2);

    EXPECT_TRUE(node2.prev() == &node1);
    EXPECT_TRUE(node2.next() == NULL);
    EXPECT_TRUE(node2.data() == 0);
}

TEST(ring_node, append_btw_2nodes)
{
	sg::Node<int32_t> node1;
	sg::Node<int32_t> node2;
	sg::Node<int32_t> node3;

	node2.append(&node1);
	node3.append(&node1);
    EXPECT_TRUE(node1.prev() == NULL);
    EXPECT_TRUE(node1.next() == &node3);
    EXPECT_TRUE(node1.data() == 0);

    EXPECT_TRUE(node2.prev() == &node3);
    EXPECT_TRUE(node2.next() == NULL);
    EXPECT_TRUE(node2.data() == 0);

    EXPECT_TRUE(node3.prev() == &node1);
    EXPECT_TRUE(node3.next() == &node2);
    EXPECT_TRUE(node3.data() == 0);
}

TEST(ring_node, append_after_2nodes)
{
	sg::Node<int32_t> node1;
	sg::Node<int32_t> node2;
	sg::Node<int32_t> node3;

	node2.append(&node1);
	node3.append(&node2);
    EXPECT_TRUE(node1.prev() == NULL);
    EXPECT_TRUE(node1.next() == &node2);
    EXPECT_TRUE(node1.data() == 0);

    EXPECT_TRUE(node2.prev() == &node1);
    EXPECT_TRUE(node2.next() == &node3);
    EXPECT_TRUE(node2.data() == 0);

    EXPECT_TRUE(node3.prev() == &node2);
    EXPECT_TRUE(node3.next() == NULL);
    EXPECT_TRUE(node3.data() == 0);
}

TEST(ring_node, detach)
{
	sg::Node<int32_t> node1;
	sg::Node<int32_t> node2;
	sg::Node<int32_t> node3;

	node2.append(&node1);
	node3.append(&node2);
	node2.detach();

    EXPECT_TRUE(node1.prev() == NULL);
    EXPECT_TRUE(node1.next() == &node3);
    EXPECT_TRUE(node1.data() == 0);

    EXPECT_TRUE(node2.prev() == NULL);
    EXPECT_TRUE(node2.next() == NULL);
    EXPECT_TRUE(node2.data() == 0);

    EXPECT_TRUE(node3.prev() == &node1);
    EXPECT_TRUE(node3.next() == NULL);
    EXPECT_TRUE(node3.data() == 0);
}

