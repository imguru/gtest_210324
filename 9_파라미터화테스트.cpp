

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



// 1. 배열
TEST(PrimeTest, IsPrime2) {
	int data[] = {
		2, 3, 5, 7, 11, 13, 17, 19, 15// ....
	};

	for (int i = 0 ; i < sizeof(data) / sizeof(data[0]) ; ++i) {
		EXPECT_TRUE(IsPrime(data[i])) << "Wrong input: " << data[i];
	}
}

// 2. 나열
TEST(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_TRUE(IsPrime(7));
	EXPECT_TRUE(IsPrime(11));
	EXPECT_TRUE(IsPrime(13));
	EXPECT_TRUE(IsPrime(17));
	EXPECT_TRUE(IsPrime(19));
}
