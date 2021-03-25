
#include <string>

class FileSystem {
public:
	virtual ~FileSystem() {}

	virtual bool IsValid(const std::string& filename) {
		// ...
		return false;
	}
};

class Logger {
public:
	// file.log
	//  : 확장자를 제외한 이름이 5글자 이상이어야 한다.
	bool IsValidLogFilename(const std::string filename) {
		//------ SUT	
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}
		//------

		FileSystem* fileSystem = new FileSystem;
		return fileSystem->IsValid(filename);
	}
};

#include <gtest/gtest.h>

//----------------
// Logger에 5글 자 이상의 파일을 전달하였을 때, true를 반환하는지 검증하고 싶다.
TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string validFilename = "valid_file_name.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

// Logger에 5글자 미만의 파일을 전달하였을 때, false를 반환하는지 검증하고 싶다.
TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string invalidFilename = "bad.log";
	
	bool actual = logger.IsValidLogFilename(invalidFilename);

	EXPECT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}




