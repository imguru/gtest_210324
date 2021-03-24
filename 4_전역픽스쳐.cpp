
// 4_전역픽스쳐(Global Fixture)
//  => xUnit Test Framework의 기능이 아닌 Google Test 고유의 기능입니다.
//  => 프로그램 시작 - SetUp
//     프로그램 종료 - TearDown


#include <gtest/gtest.h>

// 주의사항: Google Test Framework에 사용자 정의 객체를 등록할 경우,
//           반드시 힙에 생성해야 합니다.
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
//  1) main 함수 직접 구현하는 경우 - main : 권장하는 방식
//   => 심볼 충돌이 발생하는 경우, 라이브러리 안에서 gtest_main.o을 제거해야 합니다.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	testing::AddGlobalTestEnvironment(new MyTestEnvironment);

	return RUN_ALL_TESTS();
}

//  2) main 함수를 라이브러리에 포함한 경우 - 전역 변수
// testing::Environment* my_env = testing::AddGlobalTestEnvironment(new MyTestEnvironment);


TEST(SampleTest, foo) {}
TEST(SampleTest, goo) {}

TEST(MyTest, foo) {}
TEST(MyTestSample, foo) {}



// Fixture
//   1) Fixture - xUnit            => 신선한 픽스쳐 전략
//     - SetUp / TearDown
//   2) Suite Fixture - xUnit      => 신선한 픽스쳐 전략으로 인해 느린 테스트 문제가 발생하는 경우 => 공유 픽스쳐 전략
//     - SetUpTestSuite / TearDownTestSuite
//
//   //--------------
//   3) Global Fixture - Google Test => 라이브러리 초기화 / 해지
//     - Environment::SetUp / Environment::TearDown













