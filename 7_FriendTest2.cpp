
// 7_FriendTest2.cpp
#if 0
class User {
private:
	int age;

public:
	User() : age(42) {}

	void Do() {
		age = 100;
	}
};
#endif

// private 필드나 메소드에 접근해야 하는 경우, FRIEND_TEST 를 사용해야 합니다.

// #define private public
// #define class struct
#include "User.h"
// #undef private
// #undef class

#include <gtest/gtest.h>

TEST(UserTest, Do) {
	User user;

	user.Do();

	EXPECT_EQ(user.age, 100);
}

