
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
NOTE: You can safely ignore the above warning unless this call should not happen.  Do not suppress it by blindly adding an EXPECT_CALL() if you don't mean to enforce the call.  See https://github.com/google/googletest/blob/master/googlemock/docs/cook_book.md#knowing-when-to-expect for details.
#endif
// 이유: Go에 대해서 MOCK_METHOD를 하였는데, 호출 여부를 검증하고 있지 않다.
// 1. NaggyMock - 기본
//   - 관심 없는 호출에 대해서 경고를 발생시킨다.
//   - 테스트의 결과에는 영향이 없습니다.


TEST(UserTest, Say) {
	MockUser mock;

	EXPECT_CALL(mock, Say());
	
	UseUser(&mock);
}




