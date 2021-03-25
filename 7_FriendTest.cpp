
// 7_FriendTest.cpp
class User {
protected:
	int age;

public:
	User() : age(42) {}

	void Do() {
		age = 100;
	}
};

#include <gtest/gtest.h>

// 테스트 전용 하위 클래스
//  - 접근하고자 하는 SUT의 필드나 메소드가 protected인 경우
//  - C++ / Java: 부모의 protected 접근 지정자를 public으로 변경하는 것을 허용합니다.
//
class TestUser : public User {
public:
	using User::age;  // protected ->public
};

TEST(UserTest, Do) {
	// User user;
	TestUser user;

	user.Do();

	EXPECT_EQ(user.age, 100);
}

