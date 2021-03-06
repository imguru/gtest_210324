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

//-------
// Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해서 준비해야 하는 모든 것을
//         테스트 픽스쳐 라고 합니다.
//         픽스쳐를 구성하는 모든 로직 부분을 "픽스쳐를 설치(Set Up)한다" 라고 합니다.

// 픽스쳐 설치 방법
//  1. Inline Fixture Setup
//    : 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
//    장점: 픽스쳐를 설치하는 과정과 검증 로직이 테스트 함수 안에 존재하기 때문에
//          인과관계를 쉽게 분석할 수 있다.
//    단점: 모든 테스트 코드 안에서 '코드 중복'이 발생합니다.


#include <gtest/gtest.h>

#define SPEC printf

TEST(CalculatorTest, Plus_2Plus2_Displays4) {
	SPEC("2 더하기 2를 하였을 때 4가 나오는지 검증한다.\n");
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














