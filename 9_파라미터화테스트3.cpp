
#include <gtest/gtest.h>

struct Input {
	int arg1;
	int arg2;

	Input(int a, int b) : arg1(a), arg2(b) {}
};

class SampleTest : public testing::TestWithParam<Input> {
};

using testing::Values;
INSTANTIATE_TEST_SUITE_P(InputValues, SampleTest, 
	Values(Input(10, 20), Input(30, 40)));

TEST_P(SampleTest, InputValues) {
	Input input = GetParam();
	printf("%d, %d\n", input.arg1, input.arg2);
}


#if 0
// 입력 파라미터가 여러개인 경우 
enum Color { BLACK, RED, WHITE };

// "Cat" - BLACK / RED / WHITE
// "Dog" - BLACK / RED / WHITE

class AnimalTest : public testing::TestWithParam<std::tuple<const char*, Color>> {
};

using testing::Combine;
using testing::Values;
INSTANTIATE_TEST_SUITE_P(AnimalVariations, AnimalTest, 
	Combine(Values("Cat", "Dog"), Values(BLACK, RED, WHITE)));

TEST_P(AnimalTest, AnimalLooks) {
	std::tuple<const char*, Color> data = GetParam();
		
	const char* animal = std::get<0>(data);
	Color color = std::get<1>(data);

	printf("%s(%d)\n", animal, color);
}
#endif



