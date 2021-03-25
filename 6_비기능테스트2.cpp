
// 6_비기능테스트.cpp
//  : 기능적인 동작 뿐 아니라 성능이나 메모리 등의 비기능적인 부분을 검증한다.

#include <string>
#include <gtest/gtest.h>
#include <unistd.h>

bool OpenFile(const std::string& filename) {
	sleep(2);
	return true;
}

// 방법 2.  시간을 측정해서 실패하는 사용자 정의 단언문을 만들어봅시다.
#define EXPECT_TIMEOUT(fn, sec)  \
	do {															\
	  time_t startTime = time(0);        							\
	  fn; 														    \
	  time_t duration = time(0) - startTime;						\
	  EXPECT_LE(duration, sec) << duration << "초가 걸렸습니다.";	\
	} while(0)

// OpenFile은 1초 이내에 동작해야 합니다.

TEST(SampleTest, OpenFile) {
	int startTime;

	EXPECT_TIMEOUT(OpenFile("hello.txt"), 1);
}

#if 0
TEST(SampleTest, OpenFile) {
	// ----
	
	time_t startTime = time(0);

	OpenFile("hello.txt");

	time_t duration = time(0) - startTime;
	EXPECT_LE(duration, 1) << duration << "초가 걸렸습니다.";

	// ----
}
#endif
