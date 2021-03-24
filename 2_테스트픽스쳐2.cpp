// 2_테스트픽스쳐.cpp

class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	// 제품 코드 변경 발생!!!
	// Calculator(int n) {}
};

#define SPEC printf
//-------
// Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해서 준비해야 하는 모든 것을
//         테스트 픽스쳐 라고 합니다.
//         픽스쳐를 구성하는 모든 로직 부분을 "픽스쳐를 설치(Set Up)한다" 라고 합니다.

// 픽스쳐 설치 방법
//  2. Delegate Setup(위임 설치)
//   : 테스트 케이스 안에서 발생하는 픽스쳐 설치에 대한 코드를 별도의 테스트 유틸리티 함수를 통해 모듈화한다.

#include <gtest/gtest.h>


// TEST(SampleTest, foo) {}  // class SampleTest_foo : public testing::Test
// TEST(SampleTest, goo) {}  // class SampleTest_goo : public testing::Test

//              testing::Test
//                    |
//                    |
//      SampleTest.foo / SampleTest.goo         


// class SampleTest : public testing::Test {};
// TEST_F(SampleTest, foo) {} // class SampleTest_foo : public SampleTest
// TEST_F(SampleTest, goo) {} // class SampleTest_goo : public SampleTest

//              testing::Test
//                   |
//               SampleTest  
//                   |
//     SampleTest.foo / SampleTest.goo

// 1) 명시적인 Test Suite class 정의해야 합니다.
class CalculatorTest : public testing::Test {
// public:
// private:
protected:
	// 주의 사항: 테스트 케이스에서 접근하기 위해서는 반드시 protected 이상 이어야 합니다.
	Calculator* Create() { return new Calculator; }
	// Test Utility Method - Creation Method
};

//      TEST: 암묵적인 TestSuite class를 사용한다.
// 2) TEST_F: 매크로를 통해 테스트 케이스를 생성해야 합니다.
TEST_F(CalculatorTest, Plus_2Plus2_Displays4) {
	SPEC("2 더하기 2를 하였을 때 4가 나오는지 검증한다.\n");
	Calculator* calc = Create();

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}

TEST_F(CalculatorTest, PlusTest) {
	Calculator* calc = Create();

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	if (calc->Display() != 4) {
		// FAIL();
		// 실패의 원인을 명시해야 한다.
		FAIL() << "2+2 하였을 때 4가 아닙니다.";
	} else {
		SUCCEED();
	}
}














