
#include <gtest/gtest.h>

bool foo(int a, int b) {
	return true;
}

struct Input {
	int arg1;
	int arg2;

	bool result;
};

class SampleTest : public testing::TestWithParam<Input> {

};

using testing::Values;
INSTANTIATE_TEST_SUITE_P(InputValues, SampleTest,
	Values(Input{10, 20, true}));

TEST_P(SampleTest, foo) {
	Input input = GetParam();

	EXPECT_EQ(foo(input.arg1, input.arg2), input.result);
}

