
// 6_비기능테스트.cpp
//  : 기능적인 동작 뿐 아니라 성능이나 메모리 등의 비기능적인 부분을 검증한다.

#include <string>
#include <gtest/gtest.h>
#include <unistd.h>

bool OpenFile(const std::string& filename) {
	sleep(2);
	return true;
}

// 방법 1. TestSuite - SetUp / TearDown을 이용하는 방법.
class SampleTest : public testing::Test {
protected:
	time_t startTime;
	void SetUp() override {
		startTime = time(0);
	}

	void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_LE(duration, 1) << "시간 초과: " << duration << "초 초과";
	}
};


TEST_F(SampleTest, OpenFile) {
	EXPECT_TRUE(OpenFile("hello.txt"));
}


#if 0
// OpenFile은 1초 이내에 동작해야 합니다.
TEST(SampleTest, OpenFile) {
	// ----
	EXPECT_TRUE(OpenFile("hello.txt"));
	// ----
}
#endif
