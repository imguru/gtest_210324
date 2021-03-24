// 2_테스트픽스쳐.cpp
class Calculator {
public:
	double Display() { return 4; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	// 제품 코드 변경 발생!!!
	// Calculator(int n) {}
};

#define SPEC printf

// 픽스쳐 설치 방법
//  3. Implicit Setup/TearDown(암묵적 설치/해체)
//   : 여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp() / TearDown() 함수에서 생성한다.
//   => xUnit Test Framework 기능
//   장점: 테스트 코드 중복을 제거하고, 꼭 필요하지 않은 상호작용(설치) 캡슐화할 수 있다.
//   단점: 픽스쳐 설치 코드가 테스트 함수 밖에 존재하기 때문에, 테스트 함수만으로 테스트 코드를 이해하기 어려울 수 있다.
#include <gtest/gtest.h>

// xUnit Test Pattern 에서 테스트 케이스를 구성하는 방법
//  => 4단계 테스트 패턴(Four Phase Test Pattern)
//   1단계: 테스트의 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 집어넣는 작업을 한다. - SetUp()
//   2단계: SUT와 상호작용한다.   - TestCase TestBody
//   3단계: 기대 결과를 단언한다. - TestCase TestBody
//   4단계: 테스트의 픽스쳐를 해체해서 테스트 시작 이전의 상태로 돌려놓는다. - TearDown()


// xUnit Test Framework이 TestCase를 수행하는 흐름
//  => 신선한 픽스쳐 전략.
//  RUN_ALL_TESTS();
//    CalculatorTest* ts = new CalculatorTest;
//    ts->SetUp();
//    ts->TestBody1();
//    ts->TearDown();
//    delete ts;
//
//    CalculatorTest* ts = new CalculatorTest;
//    ts->SetUp();
//    ts->TestBody2();
//    ts->TearDown();
//    delete ts;

class CalculatorTest : public testing::Test {
protected:
	CalculatorTest() { printf("CalculatorTest()\n"); }
	~CalculatorTest() { printf("~CalculatorTest()\n"); }

	Calculator* calc;

	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}

	void TearDown() override {
		printf("TearDown()\n");
		delete calc;
	}
};

TEST_F(CalculatorTest, Plus_2Plus2_Displays4) {
	SPEC("2 더하기 2를 하였을 때 4가 나오는지 검증한다.\n");
	printf("TestBody() - Plus_2Plus2_Displays4\n");
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
	// 테스트가 실패할 경우, 이후의 코드는 수행되지 않습니다.
}

TEST_F(CalculatorTest, PlusTest) {
	printf("TestBody() - PlusTest\n");
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	if (calc->Display() != 4) {
		FAIL() << "2+2 하였을 때 4가 아닙니다.";
	} else {
		SUCCEED();
	}
}














