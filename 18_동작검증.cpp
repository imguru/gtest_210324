
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
	p->Go(10, 20);
	p->Go(10, 20);
	p->Go(10, 20);
}

TEST(UserTest, Sample2) {
	MockUser mock;

	// EXPECT_CALL(mock, Go(10, 20)).Times(3);
	// EXPECT_CALL(mock, Go(10, 20)).Times(AtMost(2));
	// EXPECT_CALL(mock, Go(10, 20)).Times(AnyNumber());
	EXPECT_CALL(mock, Go(10, 20)).Times(Between(1, 3));
	
	Sample2(&mock);
}

void Sample3(User* p) {
	p->Go(11, 21);
	p->Go(12, 22);
	p->Go(13, 23);
}


// Matcher 이용해서 인자에 대한 효과적인 검증이 가능합니다.
//  => Hamcrest Mathcer
using testing::Eq;  // ==
using testing::_;   // 무조건 true
using testing::Lt;  // <
using testing::Gt;  // > 
using testing::Le;  // <=
using testing::Ge;  // >=

TEST(UserTest, Sample3) {
	MockUser mock;

	// EXPECT_CALL(mock, Go(Eq(10), _)).Times(3);
	// EXPECT_CALL(mock, Go(10, _)).Times(3);

	// arg1 > 10 && arg2 < 30
	EXPECT_CALL(mock, Go(Gt(10), Lt(30))).Times(3);
#if 0
	EXPECT_CALL(mock, Go(10, 21));
	EXPECT_CALL(mock, Go(10, 22));
	EXPECT_CALL(mock, Go(10, 23));
#endif
	
	Sample3(&mock);
}











