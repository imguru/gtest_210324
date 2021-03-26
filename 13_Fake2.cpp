#include <string>

class User {
	std::string name;
	int age;
public:
	User(const std::string n, int a) : name(n), age(a) {}

	std::string GetName() const {
		return name;
	}

	int GetAge() const {
		return age;
	}
};

struct IDatabase {
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;

	// ...
};

class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User* p) {
		// ... SUT
		database->SaveUser(p->GetName(), p);
	}

	User* Load(const std::string& name) {
		// ... SUT
		return database->LoadUser(name);
	}
};

#include <gmock/gmock.h>
#include <map>

class MockDatabase : public IDatabase {
public:
	MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
	MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));
};

bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

bool operator!=(const User& lhs, const User& rhs) {
	return !(lhs == rhs);
}

// 사용자 정의 객체가 문자열로 표현될 수 있도록 만들어준다.
std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User(name=" << user.GetName() << ", age=" << user.GetAge() << ")";
}

using testing::NiceMock;
TEST(UserManagerTest, Save) {
	NiceMock<MockDatabase> fake;
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);
	// =: capture by value
	// &: capture by reference
	ON_CALL(fake, LoadUser).WillByDefault([&](const std::string& name) {
		return &expected;
	});

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	EXPECT_NE(actual, nullptr) << "Load 하였을 때";
	EXPECT_EQ(expected, *actual) << "Load 하였을 때";
}






