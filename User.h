#ifndef USER_H
#define USER_H

#include <gtest/gtest.h> // !!!

class User {
// private:
	int age;

public:
	User() : age(42) {}

	void Do() {
		age = 100;
	}

	FRIEND_TEST(UserTest, Do);
};

#endif
