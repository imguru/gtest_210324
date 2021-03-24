
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
// 1. Arrange(Given): 객체를 생성하고, 필요한 경우 설정하고 준비한다.
// 2. Act(When): 객체에 작용을 가한다.
// 3. Assert(Then): 기대하는 바를 단언한다.

// TDD(Test Driven Development) vs BDD(Behavior Driven Developmen)
// => 용어적인 차이(사람의 말과 가깝게 사용하자)
//    행위 기반 검증

// 테스트 코드 품질
// 1. 가독성
// 2. 유지보수성
//  => 테스트 코드(테스트 케이스) 안에서 제어 구문(반복문, 조건문, 예외처리)의 발생을 최소화해야 한다.
// 3. 신뢰성

#define SPEC printf

// 테스트의 이름에 테스트 시나리오가 반영되는 것이 좋다.
//  => ex) 테스트대상함수_시나리오_기대값
TEST(CalculatorTest, Plus_2Plus2_Displays4) {
	// Arrange(Given)
	SPEC("2 더하기 2를 하였을 때 4가 나오는지 검증한다.\n");
	Calculator* calc = new Calculator;
	// Act(When)
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();
	// Assert(Then)
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














