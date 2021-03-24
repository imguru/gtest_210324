
#include <string>
#include <unistd.h>

class Database {
public:
	void Connect() {}
	void Disconnect() {}

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return true; }
};

//-----------------------
#include <gtest/gtest.h>

class DatabaseTest : public testing::Test {
protected:
	Database* database;
	
	DatabaseTest() : database(nullptr) {}

	void SetUp() override {
		database = new Database;
		database->Connect();
	}

	void TearDown() override {
		database->Disconnect();
		delete database;
	}
};


TEST_F(DatabaseTest, Login) {
	database->Login("test_id", "test_password");

	ASSERT_TRUE(database->IsLogin()) << "로그인 하였을 때";
}

TEST_F(DatabaseTest, Logout) {
	database->Login("test_id", "test_password");
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) << "로그아웃 하였을 때";
}

#if 0
TEST(DatabaseTest, Login) {
	Database* database = new Database;
	database->Connect();

	database->Login("test_id", "test_password");

	ASSERT_TRUE(database->IsLogin()) << "로그인 하였을 때";

	database->Disconnect();
	delete database;
}

TEST(DatabaseTest, Logout) {
	Database* database = new Database;
	database->Connect();

	database->Login("test_id", "test_password");
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) << "로그아웃 하였을 때";

	database->Disconnect();
	delete database;
}
#endif






