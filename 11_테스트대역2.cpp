#include <string>

// 테스트 대역은 무조건 적용할 수 없습니다.
//  => 제품 코드가 테스트 대역을 적용할 수 있도록 설계되어 있어야 합니다.

// 테스트 대역을 적용할 수 있는 설계
//  => 핵심: 
//    - 약한 결합: 협력 객체의 구체적인 타입이 아닌 추상 클래스나 인터페이스에 의존하는 것
//                 협력 객체를 직접 생성하면 안됩니다.
//				   외부에서 생성해서 전달 받아야 합니다. => DI(Dependency Injection)
//
//				   의존성 주입 방법
//				    - 생성자 주입: 협력 객체가 필수적일 경우
//				    - 메소드 주입: 협력 객체가 필수적이지 않을 경우
//
//					"의존성 주입을 직접 구현해야 사용한다" - 가난한 자의 의존성 주입
//					 => 보일러플레이트 
//
//					 "의존성 주입 프레임워크를 사용하면 보일러플레이트를 효과적으로 제거할 수 있습니다."
//					 Java: Dagger2
//					 C++: https://github.com/google/fruit(참고)
//
//					 A / B / C
//
//					 A a;
//					 B b;
//					 C c;
//					 X x(&a, &b, &c);
//
//				   SOLID - 객체 지향 5대 원칙(로버트 C 마틴)
//				     SRP: 단일 책임의 원칙
//				     OCP: 개방 폐쇄의 원칙
//				     LSP: 리스코프 치환 원칙
//				     ISP: 인터페이스 분리 원칙
//				     DIP: 의존 관계 역전 원칙
//				       => 협력 객체의 구처젝인 타입이 아닌 추상 개념에 의존해야 한다.
//
//    - 강한 결합: 협력 객체의 구체적인 타입에 의존하는 것

// 1. Interface 도입
struct IFileSystem {
	virtual bool IsValid(const std::string& filename) = 0;

	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	virtual ~FileSystem() {}

	bool IsValid(const std::string& filename) override {
		// ...
		return false;
	}
};

// FileSystem fs;
// Logger logger(&fs);

// SUT를 테스트 대역을 적용할 수 있는 설계로 변경하는 작업 - 틈새 만들기
//  => 기존의 사용법과 동일하게 만드는 것이 좋습니다.
class Logger {
public:
	Logger(IFileSystem* p = nullptr) : fileSystem(p) {
		if (fileSystem == nullptr) {
			fileSystem = new FileSystem;
		}
	}

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

		// IFileSystem* fileSystem = new FileSystem;
		return fileSystem->IsValid(filename);
	}

private:
	IFileSystem* fileSystem;
};

#include <gtest/gtest.h>

// Test Double
class FileSystemTestDouble : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		return true;  // !!!!
	}
};


// Logger에 5글 자 이상의 파일을 전달하였을 때, true를 반환하는지 검증하고 싶다.
TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	FileSystemTestDouble fs;
	Logger logger(&fs); // !!!!
	std::string validFilename = "valid_file_name.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

// Logger에 5글자 미만의 파일을 전달하였을 때, false를 반환하는지 검증하고 싶다.
TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	FileSystemTestDouble fs;
	Logger logger(&fs);
	std::string invalidFilename = "bad.log";
	
	bool actual = logger.IsValidLogFilename(invalidFilename);

	EXPECT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}
#if 0
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
#endif

// 용어적인 부분이 정리가 안되어 있었습니다.
//  => xUnit Test Pattern
//     - Test Double => 이전에는 Mock이라고 불렸습니다. => Mockist
//     1) Test Stub
//     2) Fake Object
//     3) Test Spy
//     4) Mock Object
//     5) Dummy Object => 타입을 맞추는 목적




















