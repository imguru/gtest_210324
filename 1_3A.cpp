
// 1_3A.cpp
//  : 단위 테스트 케이스를 구성하는 방법.

//-------
// SUT(System Under Test)
//  - 테스트 대상 시스템
//  = CUT(Class Under Test / Code Under Test)

class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

//-------

#include <gtest/gtest.h>

// TestSuite - 테스트 대상 클래스의 마지막에 Test / Spec 이름을 붙입니다.
//  => CalculatorTest / CalculatorSpec
//  => Test Suite class per class

// 3A
// 1. Arrange: 객체를 생성하고, 필요한 경우 설정하고 준비한다.
// 2. Act: 객체에 작용을 가한다.
// 3. Assert: 기대하는 바를 단언한다.

// 테스트 코드 품질
// 1. 가독성
// 2. 유지보수성
//  => 테스트 코드(테스트 케이스) 안에서 제어 구문(반복문, 조건문, 예외처리)의 발생을 최소화해야 한다.
// 3. 신뢰성

TEST(CalculatorTest, PlusTest2) {
	Calculator* calc = new Calculator;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}

TEST(CalculatorTest, PlusTest) {
	Calculator* calc = new Calculator;

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














