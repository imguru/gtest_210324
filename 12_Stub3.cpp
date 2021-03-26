
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
#include <gmock/gmock.h>

class MockTime : public Time {
public:
	MOCK_METHOD(std::string, GetCurrentTime, (), (override));
};

using testing::Return;
using testing::NiceMock;

TEST(UserTest, Do) {
	NiceMock<MockTime> time;
	ON_CALL(time, GetCurrentTime).WillByDefault(Return("00:00"));  // Stub!!
	User user(&time);

	int actual = user.Do();

	EXPECT_EQ(42, actual);
}
#if 0
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
#endif




























