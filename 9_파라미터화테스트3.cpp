
#include <gtest/gtest.h>

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



