
#include <gmock/gmock.h>

struct Calc {
	virtual ~Calc() {}

	virtual int Add(int a, int b) { return a + b; }
	virtual int Sub(int a, int b) { return a - b; }
};

class MockCalc : public Calc {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Sub, (int a, int b), (override));
};

void Sample(Calc* p) {
	printf("Add: %d\n", p->Add(10, 20));
	printf("Sub: %d\n", p->Sub(10, 20));
}

// Google Mock는 Mocking Method의 결과를 제어할 수 있는 기능을 제공합니다.
//  => Stub / Fake
// ON_CALL(...).WillByDefault(...)

using testing::Return;

TEST(CalcTest, Sample) {
	MockCalc mock;
	ON_CALL(mock, Add).WillByDefault(Return(10));
	ON_CALL(mock, Sub).WillByDefault([](int a, int b) {
		return a - b;
	});

	EXPECT_CALL(mock, Add);
	EXPECT_CALL(mock, Sub);

	Sample(&mock);
}



