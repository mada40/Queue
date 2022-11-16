#include "tqueue.h"

#include <gtest.h>

TEST(TDynamicQueue, can_create)
{
	ASSERT_NO_THROW(TDynamicQueue<int> q);
}

TEST(TDynamicQueue, can_push)
{
	TDynamicQueue<int> q;
	ASSERT_NO_THROW(q.push(5));
}

TEST(TDynamicQueue, cant_pop_empty_queue)
{
	TDynamicQueue<int> q;
	ASSERT_ANY_THROW(q.pop());
}

TEST(TDynamicQueue, can_pop_queue)
{
	TDynamicQueue<int> q;
	q.push(5);
	ASSERT_NO_THROW(q.pop());
}

TEST(TDynamicQueue, front_is_equal_to_first_in)
{
	TDynamicQueue<int> q;
	int EL = 5;
	q.push(EL);
	int tmp = q.front();
	EXPECT_EQ(tmp, EL);
}

TEST(TDynamicQueue, can_check_is_empty)
{
	TDynamicQueue<int> q;
	EXPECT_EQ(q.empty(), true);
}

TEST(TDynamicQueue, can_get_size)
{
	TDynamicQueue<int> q;
	for (int i = 0; i < 100; i++)
		q.push(2 * i + 100);
	EXPECT_EQ(q.size(), 100);
}

TEST(TDynamicQueue, can_create_copied_queue)
{
	TDynamicQueue<int> q;
	q.push(580);
	q.push(550);
	q.pop();
	q.push(32);
	ASSERT_NO_THROW(TDynamicQueue<int> q1(q));
}

TEST(TDynamicQueue, copied_matrix_is_equal_to_source_one)
{
	TDynamicQueue<int> q;
	q.push(580);
	q.push(550);
	q.pop();
	q.push(32);
	TDynamicQueue<int> q1(q);
	EXPECT_EQ(q1, q);
}
	
TEST(TDynamicQueue, copied_queue_has_its_own_memory)
{
	TDynamicQueue<int> q1;
	q1.push(5);
	TDynamicQueue<int> q2(q1);
	q2.pop(); q2.push(58);
	int tm1 = q1.front();
	int tm2 = q2.front();
	EXPECT_NE(q1.front(), q2.front());
}

TEST(TDynamicQueue, can_assign_queue_to_itself)
{
	TDynamicQueue<int> q;
	q.push(580);
	q.pop();
	q.push(32);
	ASSERT_NO_THROW(q = q);
}

TEST(TDynamicQueue, pop_reduces_size)
{
	TDynamicQueue<int> q;
	q.push(580);
	q.push(585);
	q.push(589);
	q.pop();
	EXPECT_EQ(q.size(), 2);
}

TEST(TDynamicQueue, loop_1push1pop_after_100pop)
{
	TDynamicQueue<int> q;
	const int N = 100;
	for (int i = 0; i < N; i++)
	{
		q.push(i - 100);
	}
	for (int i = 0; i < 1e7; i++)
	{
		q.push(i * 2 + 1);
		q.pop();
	}
	EXPECT_LE(q.capacity(), N * q.COEFF);
}


