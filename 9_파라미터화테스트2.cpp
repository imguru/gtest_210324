// SUT
bool IsPrime(int value) {
	for (int i = 2 ; i < value ; ++i) {
		if (value % i == 0)
			return false;
	}

	return true;
}

//------
#include <gtest/gtest.h>

// Parameterized Test Pattern
//  => xUnit Test Framework이 제공하는 기능입니다.
//  : 입력 데이터를 바꿔가면서, 반복 검사하는 데이터 중심의 테스트에서 코드 중복을 없앨 수 있습니다.

// 1. TestSuite class
// class PrimeTest : public testing::Test {};

// TestWithParam<InputType>
class PrimeTest : public testing::TestWithParam<int> {

};

// 2. Data Set 정의
//  - INSTANTIATE_TEST_CASE_P : 1.10 이전
//  - INSTANTIATE_TEST_SUITE_P : 1.10 이후

// INSTANTIATE_TEST_SUITE_P(변수명, TestSuiteName, 데이터) 

using testing::Values;
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, Values(2, 3, 5, 7, 11, 13, 17, 19, 23));


// 3. TestCase를 만들면 됩니다.
//  - TEST: 암묵적인 TestSuite
//  - TEST_F: 명시적인 TestSuite   - testing::Test
//  - TEST_P: 파라미터화 TestSuite - testing::TestWithParam<T>

TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}

TEST_P(PrimeTest, IsPrime2) {
	EXPECT_TRUE(IsPrime(GetParam()));
}










