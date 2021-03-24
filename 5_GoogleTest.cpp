#include <gtest/gtest.h>
#include <string>

// ASSERT_XX: 단언문이 실패할 경우, 이후의 코드는 수행되지 않는다.
//  => 죽은 단언문의 문제가 발생합니다.
//  => 하나의 테스트 케이스 안에 여러 개의 단언문을 사용하는 것이 좋지 않다.
//   : 테스트 케이스가 많아질 수 있다.
//
//  > GoogleTest는 고유의 단언 매크로를 제공합니다.
// EXPECT_XX: 단언문이 실패하더라도, 이후의 코드는 계속 수행됩니다.
//            하나의 단언문이 실패하면, 테스트의 결과는 실패가 됩니다.


// ASSERT_EQ / TRUE / FALSE / LT / GT / LE / GE
// EXPECT_EQ / TRUE / FALSE / LT / GT / LE / GE
TEST(GoogleTest, Sample1) {
	int expected = 42;

	int actual1 = 41;
	int actual2 = 41;

	// ASSERT_EQ(expected, actual1) << "Reason 1";
	// ASSERT_EQ(expected, actual2) << "Reason 2";
	
	EXPECT_EQ(expected, actual1) << "Reason 1";
	EXPECT_EQ(expected, actual2) << "Reason 2";
}
