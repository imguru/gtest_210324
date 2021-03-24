
// 4_전역픽스쳐(Global Fixture)
//  => xUnit Test Framework의 기능이 아닌 Google Test 고유의 기능입니다.
//  => 프로그램 시작 - SetUp
//     프로그램 종료 - TearDown


#include <gtest/gtest.h>

class MyTestEnvironment : public testing::Environment {
public:
	void SetUp() override {
		printf("SetUp() - MyTestEnvironment\n");
	}

	void TearDown() override {
		printf("TearDown() - MyTestEnvironment\n");
	}
};

// 설치하는 방법
//  1) main 함수 직접 구현하는 경우 - main
//  2) main 함수를 라이브러리에 포함한 경우 - 전역 변수
testing::Environment* my_env = testing::AddGlobalTestEnvironment(new MyTestEnvironment);

TEST(SampleTest, foo) {}
TEST(SampleTest, goo) {}

TEST(MyTest, foo) {}
TEST(MyTestSample, foo) {}
