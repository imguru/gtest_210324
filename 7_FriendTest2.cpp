
// 7_FriendTest2.cpp
#if 1
class User {
private:
	int age;

	void Do() {
		age = 100;
	}

public:
	User() : age(42) {}
};
#endif

// Clean code: 로버트 C 마틴
//  => private 메소드는 public 메소드의 가독성을 높이기 위해 사용해야 한다.
//     public 메소드를 통해 호출되지 않는 private 메소드는 잘못된 설계이다.
//     
//     테스트 되지 않은 private 메소드가 테스트 된 public 메소드가 보다 위험하다.

// private 필드나 메소드에 접근해야 하는 경우, FRIEND_TEST 를 사용해야 합니다.

// - 절대 사용하지 마세요.
// #define private public
// #define class struct
// #include "User.h"
// #undef private
// #undef class

#include <gtest/gtest.h>

TEST(UserTest, Do) {
	User user;

	user.Do();

	EXPECT_EQ(user.age, 100);
}

