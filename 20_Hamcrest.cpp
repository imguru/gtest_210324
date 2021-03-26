
// Hamcrest - Matcher
//  => 단언문을 사람의 문장에 가깝게 표현하게 해주는 라이브러리
//    EXPECT_EQ / NE / TRUE / FALSE ...

#include <gmock/gmock.h>

int GetAge() { return 30; }

using testing::Eq;
using testing::Gt;

TEST(HamcrestTest, Sample) {
	EXPECT_EQ(GetAge(), 100);
	EXPECT_TRUE(GetAge() > 50);

	EXPECT_THAT(GetAge(), Eq(100));
	EXPECT_THAT(GetAge(), Gt(50));
}
