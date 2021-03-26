
#include <gmock/gmock.h>

struct User {
	virtual ~User() {}

	virtual int GetAge() const = 0;
};

class MockUser : public User {
public:
	MOCK_METHOD(int, GetAge, (), (override, const));
};

void Sample(User* p) {
	// printf("%d\n", p->GetAge());
}

// 행위 기반 검증을 수행하고 있다면 - EXPECT_CALL을 사용한다면
//  EXPECT_CALL이 제공하는 기능을 통해 결과를 제어하는 것이 가능합니다.

using testing::Return;
// 1. WillOnce + WillOnce => Times(2)
// 2. WillOnce + WillOnce + WillRepeatedly => Times(atLeast(2))
// 3. WillRepeatedly  => Times(AnyNumber())

TEST(UserTest, Sample) {
	MockUser mock;

	EXPECT_CALL(mock, GetAge)
	//	.WillOnce(Return(10))
	//	.WillOnce(Return(20))
		.WillRepeatedly(Return(100));

	Sample(&mock);
}
#if 0
TEST(UserTest, Sample) {
	MockUser mock;

	EXPECT_CALL(mock, GetAge)
		.WillOnce(Return(10))
		.WillOnce(Return(20));

	Sample(&mock);
}
#endif
