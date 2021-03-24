
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

TEST(CalculatorTest, PlusTest) {
	Calculator* calc = new Calculator;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	if (calc->Display() != 4) {
		FAIL();
	} else {
		SUCCEED();
	}
}











