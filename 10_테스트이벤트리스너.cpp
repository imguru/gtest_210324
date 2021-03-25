
// 10_테스트이벤트리스너.cpp
#include <gtest/gtest.h>

class MyTestPrinter : public testing::EmptyTestEventListener {
public:
	void OnTestProgramStart(const UnitTest& /*unit_test*/) override {}
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
	void OnTestProgramEnd(const UnitTest& /*unit_test*/) override {}
};


TEST(SampleTest, foo) {
}

TEST(SampleTest, goo) {
}

TEST(SampleTest, hoo) {
}
