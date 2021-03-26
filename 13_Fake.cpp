
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

#include <gtest/gtest.h>
#include <map>

// Fake Object Pattern
//  의도: 아직 준비되지 않은 의존 객체로 인해서, 테스트 되지 않은 요구사항이 있을 때
//  방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서 문제를 해결하자.
//    1) 의존하는 객체가 준비되지 않았을 때
//    2) 의존하는 객체가 너무 느릴 때
//    3) 의존하는 객체가 사용하기 어려울 때

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void SaveUser(const std::string& name, User* user) override {
		data[name] = user;
	}

	User* LoadUser(const std::string& name) override {
		return data[name];
	}
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

TEST(UserManagerTest, Save) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);
	User expected2("Tom", testAge);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	EXPECT_NE(actual, nullptr) << "Load 하였을 때";

	// 사용자 정의 타입에 단언문을 사용하기 위해서는 
	// 연산자 오버로딩이 필요합니다.
	//  EQ(==) / NE(!=), LT(<), GT(>), LE(<=), GE(>=)
	EXPECT_EQ(expected2, *actual) << "Load 하였을 때";
}






