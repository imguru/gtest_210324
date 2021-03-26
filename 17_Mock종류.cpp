
#include <gmock/gmock.h>

struct User {
	virtual ~User() {}

	virtual void Say() = 0;
	virtual void Go() = 0;
};

//-----------
class MockUser : public User {
public:
	MOCK_METHOD(void, Say, (), (override));
	MOCK_METHOD(void, Go, (), (override));
};

void UseUser(User* p) {
	p->Say();
	p->Go();
}

#if 0
GMOCK WARNING:
Uninteresting mock function call - returning directly.
    Function call: Go()
#endif
// 이유: Go에 대해서 MOCK_METHOD를 하였는데, 호출 여부를 검증하고 있지 않다.
// 1. NaggyMock - 기본
//   - 관심 없는 호출에 대해서 경고를 발생시킨다.
//   - 테스트의 결과에는 영향이 없습니다.

// 2. NiceMock
//   - 경고를 발생시키지 않습니다.
//
// 3. StrictMock
//   - 테스트가 실패합니다.

using testing::NiceMock;
using testing::StrictMock;

TEST(UserTest, Say) {
	// MockUser mock;
	// NiceMock<MockUser> mock;
	StrictMock<MockUser> mock;

	EXPECT_CALL(mock, Say());
	
	UseUser(&mock);
}




