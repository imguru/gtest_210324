
#include <string>

struct Time {
	virtual ~Time() {}

	virtual std::string GetCurrentTime() = 0;
};

class Clock : public Time {
public:
	std::string GetCurrentTime() override {
		// 현재 시간을 문자열로 변경해서 반환한다.
		return "09:06";
	}
};

class User {
	Time* time;
public:
	User(Time* p) : time(p) {}

	int Do() {
		std::string t = time->GetCurrentTime();
		if (t == "00:00") {
			// ...
			return 42;
		}

		return 0;
	}
};

//----------
// User의 Do를 호출하였을 때, 00:00 분에 42를 반환하는지 검증하고 싶다.
#include <gtest/gtest.h>

class StubTime : public Time {
public:
	std::string GetCurrentTime() override {
		return "00:00";
	}
};

TEST(UserTest, Do) {
	// Clock time;
	StubTime time;
	User user(&time);

	int actual = user.Do();

	EXPECT_EQ(42, actual);
}




























