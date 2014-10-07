/*
 * time_test.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: gstide
 */

#include <gtest/gtest.h>

#include "timediff.h"

template <typename T>
class TimeDiffTest : public ::testing::Test {
public:
	TimeDiffTest()
	: _from(), _to(), _expected_value()
	{}
	virtual ~TimeDiffTest(){}

public:
	T _from;
	T _to;
	T _expected_value;
};
TYPED_TEST_CASE_P(TimeDiffTest);

TYPED_TEST_P(TimeDiffTest, negFrom_LT_negTo)
{
	// this test is for signed types only
	if (!std::is_signed<TypeParam>::value)
		return;

	TypeParam from = std::numeric_limits<TypeParam>::min();
	TypeParam to = -1;
	uint64_t expected_value = to - from;
	EXPECT_EQ(expected_value, time_diff(from, to));
}

TYPED_TEST_P(TimeDiffTest, negFrom_LT_posTo)
{
	// this test is for signed types only
	if (!std::is_signed<TypeParam>::value)
		return;

	TypeParam from = std::numeric_limits<TypeParam>::min();
	TypeParam to = std::numeric_limits<TypeParam>::max();
	uint64_t expected_value = to;
	expected_value -= from;
//	printf("%lld\n", expected_value);
	EXPECT_EQ(expected_value, time_diff(from, to));
}

TYPED_TEST_P(TimeDiffTest, posFrom_LT_posTo)
{
	TypeParam from = 1;
	TypeParam to = std::numeric_limits<TypeParam>::max();
	uint64_t expected_value = to - from;
	EXPECT_EQ(expected_value, time_diff(from, to));
}

TYPED_TEST_P(TimeDiffTest, negFrom_GT_negTo)
{
	// this test is for signed types only
	if (!std::is_signed<TypeParam>::value)
		return;

	TypeParam from = -1;
	TypeParam to = std::numeric_limits<TypeParam>::min();
	TypeParam temp = from - to;
	ASSERT_GE(temp, 0);
	uint64_t expected_value = std::numeric_limits<TypeParam>::max() - temp +1;
//	printf("%lld\n", expected_value);
	expected_value += std::numeric_limits<TypeParam>::max();
	expected_value += 1;
//	printf("%lld\n", expected_value);
	EXPECT_EQ(expected_value, time_diff(from, to));
}

TYPED_TEST_P(TimeDiffTest, posFrom_GT_negTo)
{
	// this test is for signed types only
	if (!std::is_signed<TypeParam>::value)
		return;

	TypeParam from = 1;
	TypeParam to = -1;
	uint64_t unsigned_type_num_max = std::numeric_limits<TypeParam>::max();
	unsigned_type_num_max *= 2;
	unsigned_type_num_max += 1;
	uint64_t expected_value = unsigned_type_num_max - 1;
	EXPECT_EQ(expected_value, time_diff(from, to));
}

TYPED_TEST_P(TimeDiffTest, posFrom_GT_posTo)
{
	TypeParam from = std::numeric_limits<TypeParam>::max();
	TypeParam to = from - 1;
	uint64_t expected_value = std::numeric_limits<TypeParam>::max();
	if (std::is_signed<TypeParam>::value) {
		expected_value *= 2;
		expected_value += 1;
	}
	EXPECT_EQ(expected_value, time_diff(from, to));
}

TYPED_TEST_P(TimeDiffTest, negFrom_EQ_negTo)
{
	// this test is for signed types only
	if (!std::is_signed<TypeParam>::value)
		return;
	TypeParam t = 0;
	EXPECT_EQ(0, time_diff(t, t));
	t = -1;
	EXPECT_EQ(0, time_diff(t, t));
	t = std::numeric_limits<TypeParam>::min();
	EXPECT_EQ(0, time_diff(t, t));
}

TYPED_TEST_P(TimeDiffTest, posFrom_EQ_posTo)
{
	TypeParam t = 0;
	EXPECT_EQ(0, time_diff(t, t));
	t = 1;
	EXPECT_EQ(0, time_diff(t, t));
	t = std::numeric_limits<TypeParam>::max();
	EXPECT_EQ(0, time_diff(t, t));
}

REGISTER_TYPED_TEST_CASE_P(TimeDiffTest
		, negFrom_LT_negTo, negFrom_LT_posTo, posFrom_LT_posTo, negFrom_GT_negTo, posFrom_GT_negTo, posFrom_GT_posTo, negFrom_EQ_negTo, posFrom_EQ_posTo);

// int8_t, uint8_t, int16_t, uint16_t,
typedef ::testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t> time_diff_test_types;
INSTANTIATE_TYPED_TEST_CASE_P(TimeDiffTest, TimeDiffTest, time_diff_test_types);

TEST(TimeDiffTest, spot_test1)
{
	int8_t from = 127;
	int8_t to = -128;
	EXPECT_EQ(1u, time_diff(from, to));
}

TEST(TimeDiffTest, spot_test2)
{
	int8_t from = -128;
	int8_t to = 127;
	EXPECT_EQ(255u, time_diff(from, to));
}

TEST(TimeDiffTest, int64_spot_test1)
{
	int64_t from = std::numeric_limits<int64_t>::min();
	int64_t to = std::numeric_limits<int64_t>::max();
	EXPECT_EQ(std::numeric_limits<uint64_t>::max(), time_diff(from, to));
}

TEST(TimeDiffTest, int64_spot_test2)
{
	int64_t from = std::numeric_limits<int64_t>::max();
	int64_t to = std::numeric_limits<int64_t>::min();
	EXPECT_EQ(1u, time_diff(from, to));
}

TEST(TimeDiffTest, int64_spot_test3)
{
	int64_t from = 1;
	int64_t to = -1;
	EXPECT_EQ(std::numeric_limits<uint64_t>::max()-1, time_diff(from, to));
}

TEST(TimeDiffTest, uint64_spot_test1)
{
	uint64_t from = std::numeric_limits<uint64_t>::min();
	uint64_t to = std::numeric_limits<uint64_t>::max();
	EXPECT_EQ(std::numeric_limits<uint64_t>::max(), time_diff(from, to));
}

TEST(TimeDiffTest, uint64_spot_test2)
{
	uint64_t from = std::numeric_limits<uint64_t>::max();
	uint64_t to = std::numeric_limits<uint64_t>::min();
	EXPECT_EQ(1u, time_diff(from, to));
}

TEST(TimeDiffTest, uint64_spot_test3)
{
	uint64_t from = 1;
	uint64_t to = -1;
	EXPECT_EQ(std::numeric_limits<uint64_t>::max()-1, time_diff(from, to));
}

