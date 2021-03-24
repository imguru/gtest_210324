
#include <gtest/gtest.h>

// 정적 라이브러리 - libgtest.a => 권장
//  - Archived
//  - 프로그램 내부에 라이브러리가 복사되기 때문에, 라이브러리가 업데이트 되면 다시 컴파일을 수행해야 합니다.
//  - 이식성이 뛰어나다.
//
// 동적 라이브러리 - libgtest.so
//  - Shared Object
//  - 프로세스가 수행될 때 라이브러리를 로드한다.
//  - 라이브러리가 업데이트되어도, 기존 프로그램을 다시 컴파일할 필요가 없다.
//  - 프로그램 내부에서 필요한 시점에 로드해서 사용할 수 있습니다.


// Google Test - 1.10
//  - 표준적이지 않은 이름을 사용하고 있었습니다.
//  - 1.10 이전
//  TestCase
//   - Test
//   - Test
//
//  - 1.10 이후(xUnit Test Pattern)
//  TestSuite
//   - TestCase
//   - TestCase

// Google Test 에서 TestCase를 추가하는 방법.
//TEST(TestSuiteName, TestCaseName)
TEST(SampleTest, Sample1) {
	// 명시적으로 테스트를 실패할 수 있습니다.
	FAIL();
}

TEST(SampleTest, Sample2) {
	// 명시적으로 성공을 표현하는 방법.
	SUCCEED();
}

// 아래 main이 코드는 거의 동일합니다.
//  => main도 라이브러리 안에 포함해서 사용하면 편리합니다.
#if 0
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif
