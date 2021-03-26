
#include <gmock/gmock.h>

// 행위 기반 검증
// 1. 함수의 호출 여부
// 2. 함수의 호출 횟수
// 3. 함수의 호출 순서
//  + 함수의 호출 인자

struct User {
	virtual ~User() {}
	
	virtual void Go(int x, int y) = 0;
	virtual void Say(const char* message) = 0;
};

//----------
class MockUser : public User {
public:
	MOCK_METHOD(void, Go, (int x, int y), (override));
	MOCK_METHOD(void, Say, (const char* message), (override));
};

void Sample1(User* p) {
	p->Go(10, 20);
	p->Say("Hello");
}

// 1. EXPECT_CALL: 호출 여부 검증
TEST(UserTest, Sample1) {
	MockUser mock;

	EXPECT_CALL(mock, Go(10, 20));
	EXPECT_CALL(mock, Say("Hello"));

	Sample1(&mock);
}



