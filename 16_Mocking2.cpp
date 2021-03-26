
#include <gmock/gmock.h>

struct Element {};

class Calc {
	int x;
public:
	virtual ~Calc() {}

	virtual int Add(Element x) {
		printf("Add\n");
	}

	// 기본 구현을 제공하고 있다면, 
	// 행위 기반 검증을 수행하고자 하는 함수에 대해서만 MOCK_METHOD를 작성하면 됩니다.
	virtual int Add(int times, Element x) {
		printf("Add2\n");
	}
};

class User {
public:
	void Add(Calc* p) {
		p->Add(10, Element{});

		// 행위 기반 검증 대상이 아닙니다.
		p->Add(Element{});
	}
};

bool operator==(const Element& lhs, const Element& rhs) {
	return true;
}

//-----------
// 의존하는 객체가 상속 가능한 클래스라면, Google Mock을 통해 Mocking 가능합니다.
class MockCalc : public Calc {
public:
	// 아래 매크로의 영향으로 Add라는 동일한 이름을 가지는 함수가 감추어집니다.
	MOCK_METHOD(int, Add, (int times, Element x), (override));

	using Calc::Add;  // 오버로딩한 함수가 MOCK_METHOD가 되어 있을 경우, 직접 호출하기 위해서는 명시적으로 선언이 필요합니다.
};

TEST(UserTest, Add) {
	User user;
	MockCalc calc;

	// 2) 직접 접근할 때, 컴파일 오류가 발생합니다.
	calc.Add(Element{}); // !!

	// 문제점
	// 1) Element 인자가 동일한지 검증하기 위해서는 연산자 오버로딩이 필요합니다.
	EXPECT_CALL(calc, Add(10, Element{}));

	user.Add(&calc);
}



























