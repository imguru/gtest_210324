
// 10_테스트이벤트리스너.cpp
#include <gtest/gtest.h>

using testing::UnitTest;
using testing::TestSuite;
using testing::TestInfo;
using testing::TestPartResult;

// Google Test
class MyTestPrinter : public testing::EmptyTestEventListener {
public:
	void OnTestProgramStart(const UnitTest& /*unit_test*/) override {
		printf(">> OnTestProgramStart\n");
	}
	void OnTestIterationStart(const UnitTest& /*unit_test*/, int /*iteration*/) override {}
	void OnEnvironmentsSetUpStart(const UnitTest& /*unit_test*/) override {}
	void OnEnvironmentsSetUpEnd(const UnitTest& /*unit_test*/) override {}
	void OnTestSuiteStart(const TestSuite& test_suite) override {
		printf(">>>> OnTestSuiteStart: %s\n", test_suite.name());
	}

	void OnTestStart(const TestInfo& test_info) override {
		// printf(">>>>> OnTestStart: %s\n", test_info.name());
		printf(">>>>> OnTestStart: %s.%s\n", test_info.test_suite_name(), test_info.name());
	}

	void OnTestPartResult(const TestPartResult& test_part_result) override {
		bool fail = test_part_result.failed();
		printf(">>>>>> OnTestPartResult: %s\n", fail ? "Failed" : "Succeed");
	}

	void OnTestEnd(const TestInfo& test_info) override {
		printf(">>>>> OnTestEnd: %s\n", test_info.name());
	}

	void OnTestSuiteEnd(const TestSuite& test_suite) override {
		printf(">>>> OnTestSuiteEnd: %s\n", test_suite.name());
	}

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

	// 기본 프린터를 삭제한다.
	delete listeners.Release(listeners.default_result_printer());

	listeners.Append(new MyTestPrinter);

	return RUN_ALL_TESTS();
}

TEST(SampleTest, foo) {
	FAIL();
}

TEST(SampleTest, goo) {
}

TEST(SampleTest, hoo) {
}
