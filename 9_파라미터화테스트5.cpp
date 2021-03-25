
#include <gtest/gtest.h>

class SampleTest : public testing::TestWithParam<int> {
};

using testing::Range;

// Values
// ValuesIn
// Range
// Combine
INSTANTIATE_TEST_SUITE_P(IntValues, SampleTest,
	Range(0, 100, 10)
	// [0, 100)
);

TEST_P(SampleTest, Sample) {
	printf("%d\n", GetParam());
}
