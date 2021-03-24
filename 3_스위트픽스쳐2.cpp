
#include <string>
#include <unistd.h>

class Database {
public:
	// 가정: Connect / Disconnect 느리다.
	void Connect() {
		sleep(2);
	}
	void Disconnect() {
		sleep(1);
	}

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return true; }
	bool IsConnect() { return true; } // !!
};

//-----------------------
#include <gtest/gtest.h>

// 문제점: 픽스쳐를 설치하거나 해체하는 과정으로 인해 "느린 테스트"의 문제가 발생하였다.
//  Slow Test(느린 테스트)
//   : 테스트가 느려서 테스트를 수행 하는 개발자의 생산성을 떨어뜨린다.
//     테스트 느려서 코드가 변경되어도 테스트를 수행하지 않는다.
//
//  해결방법: Suite Fixture SetUp / TearDown
//    => xUnit Test Framework

// ----------- Suite Fixture Setup ----- Connect(); // static
// SampleTest *ts = new SampleTest;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;
//
// SampleTest *ts = new SampleTest;
// ts->SetUp();
// ts->TestBody();
// ts->TearDown();
// delete ts;
// ----------- Suite Fixture TearDown ----- Disconnect(); // static

class DatabaseTest : public testing::Test {
protected:
	// Database* database;
	// DatabaseTest() : database(nullptr) {}
	
	static Database* database;

	// Suite Fixture SetUp / TearDown
	// 1.10 이전
	// static void SetUpTeatCase() {}
	
	static void SetUpTestSuite() {
		printf("SetUpTestSuite\n");
		database = new Database;
		database->Connect(); 
	}

	static void TearDownTestSuite() {
		printf("TearDownTestSuite\n");
		database->Disconnect();
		delete database;
	}

	// Fixture SetUp / TearDown
	void SetUp() override {
		printf("SetUp()\n");
		// database = new Database;
		// database->Connect(); 
	}

	void TearDown() override {
		printf("TearDown()\n");
		// database->Disconnect();
		// delete database;
	}
};

// 정적 멤버 변수에 대해서는 외부 정의가 필요합니다.
Database* DatabaseTest::database = nullptr;


TEST_F(DatabaseTest, Login) {
	database->Login("test_id", "test_password");

	ASSERT_TRUE(database->IsLogin()) << "로그인 하였을 때";
}

TEST_F(DatabaseTest, Logout) {
	database->Login("test_id", "test_password");
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) << "로그아웃 하였을 때";
}

TEST_F(DatabaseTest, foo) {
}

TEST_F(DatabaseTest, goo) {
}

