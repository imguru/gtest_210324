
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

// 2. 호출 횟수
//  => EXPECT_CALL(...).Times(N) - N번 호출
// - AtLeast - 적어도 N번 이상
// - AtMost  - 최대 N번 이하
// - AnyNumber
// - Between

using testing::AtLeast;
using testing::AtMost;
using testing::AnyNumber;
using testing::Between;

void Sample2(User* p) {
	// p->Go(10, 20);
	// p->Go(10, 20);
	// p->Go(10, 20);
}

TEST(UserTest, Sample2) {
	MockUser mock;

	// EXPECT_CALL(mock, Go(10, 20)).Times(3);
	// EXPECT_CALL(mock, Go(10, 20)).Times(AtMost(2));
	// EXPECT_CALL(mock, Go(10, 20)).Times(AnyNumber());
	EXPECT_CALL(mock, Go(10, 20)).Times(Between(1, 3));
	
	

	Sample2(&mock);
}













