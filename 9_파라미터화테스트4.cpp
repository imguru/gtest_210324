
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <iostream>

class StringTest : public testing::TestWithParam<std::string> {

};

using testing::Values;
using testing::ValuesIn;

#if 0
std::vector<std::string> LoadInputStrings() {
	// ...
	std::vector<std::string> v;
	v.push_back("hello1");
	v.push_back("hello2");
	v.push_back("hello3");
	v.push_back("hello4");
	v.push_back("hello");
	v.push_back("hello");
	v.push_back("hello");
	return v;
}
#endif

// ???
//  $ ./a.out < input.txt
std::vector<std::string> LoadInputStrings() {
	std::vector<std::string> v;
	
	while (!std::cin.eof()) {
		std::string input;
		std::cin >> input;
	
		v.push_back(input);
	}

	return v;
}

std::string s[] = {
	"hello", "world", "show", "me"
};

INSTANTIATE_TEST_SUITE_P(StringValues, StringTest, 
	// Values("hello", "world", "show", "me", "the", "money")
	// ValuesIn(s)
	ValuesIn(LoadInputStrings())
);

TEST_P(StringTest, Sample) {
	std::string s = GetParam();
	std::cout << s << std::endl;
}


