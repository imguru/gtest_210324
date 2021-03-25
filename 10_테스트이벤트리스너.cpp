
// 10_테스트이벤트리스너.cpp
#include <gtest/gtest.h>

using testing::UnitTest;
using testing::TestSuite;
using testing::TestInfo;
using testing::TestPartResult;

class MyTestPrinter : public testing::EmptyTestEventListener {
public:
	void OnTestProgramStart(const UnitTest& /*unit_test*/) override {
		printf(">> OnTestProgramStart\n");
	}
	void OnTestIterationStart(const UnitTest& /*unit_test*/, int /*iteration*/) override {}
	void OnEnvironmentsSetUpStart(const UnitTest& /*unit_test*/) override {}
	void OnEnvironmentsSetUpEnd(const UnitTest& /*unit_test*/) override {}
	void OnTestSuiteStart(const TestSuite& /*test_suite*/) override {}

	void OnTestStart(const TestInfo& /*test_info*/) override {}
	void OnTestPartResult(const TestPartResult& /*test_part_result*/) override {}
	void OnTestEnd(const TestInfo& /*test_info*/) override {}
	void OnTestSuiteEnd(const TestSuite& /*test_suite*/) override {}

	void OnEnvironmentsTearDownStart(const UnitTest& /*unit_test*/) override {}
	void OnEnvironmentsTearDownEnd(const UnitTest& /*unit_test*/) override {}
	void OnTestIterationEnd(const UnitTest& /*unit_test*/, int /*iteration*/) override {}
	
	void OnTestProgramEnd(const UnitTest& /*unit_test*/) override {
		printf(">> OnTestProgramEnd\n");
	}
};

// main을 정의할 필요가 있습니다.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
	listeners.Append(new MyTestPrinter);

	return RUN_ALL_TESTS();
}



TEST(SampleTest, foo) {
}

TEST(SampleTest, goo) {
}

TEST(SampleTest, hoo) {
}
