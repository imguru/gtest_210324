
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
using testing::AllOf; // &&
using testing::AnyOf; // ||

using testing::Matcher;

TEST(UserTest, Sample3) {
	MockUser mock;

	// EXPECT_CALL(mock, Go(Eq(10), _)).Times(3);
	// EXPECT_CALL(mock, Go(10, _)).Times(3);

	// arg1 > 10 && arg1 < 30
	// Matcher<int> firstArg = AllOf(Gt(10), Lt(30));
	auto firstArg = AllOf(Gt(10), Lt(30));
	// arg2 < 0  || arg2 > 20
	Matcher<int> secondArg = AnyOf(Lt(0), Gt(20));

	EXPECT_CALL(mock, Go(firstArg, secondArg)).Times(3);
#if 0
	// arg1 > 10 && arg2 < 30
	EXPECT_CALL(mock, Go(Gt(10), Lt(30))).Times(3);
	EXPECT_CALL(mock, Go(10, 21));
	EXPECT_CALL(mock, Go(10, 22));
	EXPECT_CALL(mock, Go(10, 23));
#endif
	
	Sample3(&mock);
}

struct Foo {
	virtual ~Foo() {}

	virtual void First() = 0;
	virtual void Second() = 0;
	virtual void Third() = 0;
	virtual void Forth() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, First, (), (override));
	MOCK_METHOD(void, Second, (), (override));
	MOCK_METHOD(void, Third, (), (override));
	MOCK_METHOD(void, Forth, (), (override));
};

void Sample4(Foo* p) {
	p->First();
	p->Second();
	p->Third();
	p->Forth();
}

// 3. 호출 순서 검증
//   : EXPECT_CALL은 순서를 판단하지 않습니다. - 기본
//
//   InSequence 객체
//    : EXPECT_CALL은 순서를 판단합니다.

using testing::InSequence;

TEST(FooTest, Sample4) {
	MockFoo mock;
	InSequence seq; // !!!!
	
	EXPECT_CALL(mock, First);
	EXPECT_CALL(mock, Second);
	EXPECT_CALL(mock, Third);
	EXPECT_CALL(mock, Forth);

	Sample4(&mock);
}








































