#include <gtest/gtest.h>
#include <string>

// 1.
// ASSERT_XX: 단언문이 실패할 경우, 이후의 코드는 수행되지 않는다.
//  => 죽은 단언문의 문제가 발생합니다.
//  => 하나의 테스트 케이스 안에 여러 개의 단언문을 사용하는 것이 좋지 않다.
//   : 테스트 케이스가 많아질 수 있다.
//
//  > GoogleTest는 고유의 단언 매크로를 제공합니다.
// EXPECT_XX: 단언문이 실패하더라도, 이후의 코드는 계속 수행됩니다.
//            하나의 단언문이 실패하면, 테스트의 결과는 실패가 됩니다.

// ASSERT_EQ / TRUE / FALSE / LT / GT / LE / GE
// EXPECT_EQ(==) / TRUE / FALSE / LT / GT / LE / GE
TEST(GoogleTest, Sample1) {
	int expected = 42;

	int actual1 = 42;
	int actual2 = 42;

	// ASSERT_EQ(expected, actual1) << "Reason 1";
	// ASSERT_EQ(expected, actual2) << "Reason 2";
	
	EXPECT_EQ(expected, actual1) << "Reason 1";
	EXPECT_EQ(expected, actual2) << "Reason 2";
}


// 2.
//  C-Style 문자열: const char* - strcmp
//   : EXPECT_STREQ / STRNE
//     EXPECT_STRCASEEQ / STRCASENE

//  C++ 문자열: std::string
TEST(GoogleTest, Sample2) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	EXPECT_EQ(s1, s2);

	const char* s3 = "HELLo";
	const char* s4 = s1.c_str();

	// EXPECT_EQ(s3, s4);
	// EXPECT_STREQ(s3, s4);
	EXPECT_STRCASEEQ(s3, s4);
}

// 3. double, float
//    EXPECT_DOUBLE_EQ
//    EXPECT_FLOAT_EQ
//
//    EXPECT_NEAR: 오차 범위를 직접 설정할 수 있습니다.
TEST(GoogleTest, Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	// EXPECT_EQ(a, b);
	EXPECT_DOUBLE_EQ(a, b); // 4ULP's
	                        // https://en.wikipedia.org/wiki/Unit_in_the_last_place
	EXPECT_NEAR(a, b, 0.000000000000001);
}

// 4. 예외 테스트
//  - EXPECT_THROW
//  - EXPECT_ANY_THROW
void IsValidFilename(const std::string& filename) {
	if (filename.empty()) {
		// throw 1;
		throw std::invalid_argument("filename is empty!!");
	}
}

TEST(GoogleTest, Sample4) {
	std::string emptyFilename = "";

	EXPECT_ANY_THROW(IsValidFilename(emptyFilename));
	EXPECT_THROW(IsValidFilename(emptyFilename), std::invalid_argument) << "빈 문자열을 전달하였을 때";
}

// IsValidFilename에 빈문자열을 전달할 경우, 예외가 제대로 발생하는지 여부를 검증하고 싶다.
#if 0
TEST(GoogleTest, Sample4) {
	std::string emptyFilename = "";

	try {
		IsValidFilename(emptyFilename);
		FAIL() << "기대한 예외가 발생하지 않았습니다.";
	} catch (std::invalid_argument& e) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였습니다.";
	}
}
#endif


// 5. 테스트 비활성화
// - 테스트케이스를 주석 처리한다: 잊혀진 테스트
// => TestSuite 이름 또는 TestCase의 이름이 DISABLED_ 이름으로 시작하면 비활성화됩니다.

// - 비활성화된 테스트도 포함해서 동작할 수 있는 명령어 옵션를 제공합니다.
//  $ ./a.out --gtest_also_run_disabled_tests
TEST(GoogleTest, DISABLED_Sample5) {
	// 작성 중입니다.
	FAIL() << "작성 중입니다.";
}

class DISABLED_SampleTest : public testing::Test {
};

TEST_F(DISABLED_SampleTest, foo) {
}

TEST_F(DISABLED_SampleTest, goo) {
}

// 6. 반복 테스트
//  => 변덕스러운 테스트를 확인하는 목적으로 사용할 수 있다.
//   $ ./a.out --gtest_repeat=100 --gtest_break_on_failure --gtest_shuffle
int n = 0;
TEST(GoogleTest, Sample6) {
	EXPECT_NE(++n, 50);
}


// 7. 필터
//  $ ./a.out --gtest_filter=GoogleTest.Sample1
//  $ ./a.out --gtest_filter=SampleTest*.*:-*.foo
//
//  핵심: 필터의 기능을 온전히 사용하기 위해서는 잘 협의된 이름규칙이 필요합니다.
TEST(SampleTest2, foo) {}
TEST(SampleTest2, goo) {}

TEST(SampleTest3, foo) {}
TEST(SampleTest3, goo) {}

// 8. Test Result Formatter
//  $ ./a.out --gtest_output=[xml|json]:/path/output.xml
//    xml: test_details.xml   -> xUnit Test Framework
//    json: test_details.json -> Google Test

// 9. 추가적인 정보를 기록할 수 있습니다.
TEST(GoogleTest, Sample9) {
	RecordProperty("cpu", "2.5");
	RecordProperty("mem", "512");
}






















































