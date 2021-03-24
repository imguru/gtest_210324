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

// 픽스쳐 설치 방법
//  3. 


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














