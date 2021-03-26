#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {};

	virtual void Write(Level level, const std::string& message) = 0;
};

// FileTarget / NetworkTarget / StdoutTarget
class FileTarget : DLoggerTarget {
public:
	void Write(Level level, const std::string& message) override {
		printf("File 기록 - %d(%s)\n", level, message.c_str());
	}
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* e: targets) {
			// e->Write(level, message);
			// break;
		}
	}
};

//--------------
#include <gtest/gtest.h>
#include <vector>
#include <string>

#include <algorithm> // find

// Mock Object Pattern
//  의도: 함수를 호출하였을 때 발생하는 부수 효과를 관찰할 수 없어서 테스트되지 않은 요구사항이 있을 때
//  방법: 행위 기반 검증(동작 검증)
//      - 객체에 작용을 가한 후 내부적으로 발생하는 함수의 호출 여부, 호출 순서, 호출 횟수 등을 통해 검증을 수행합니다.
//
//        상태 기반 검증(상태 검증)
//      - 객체에 작용을 가한 후 단언문을 통해 내부의 상태값의 변경을 검증한다. 

// Mock Object(모의 객체)
//  : 내부적으로 발생한 함수의 호출 여부, 횟수, 순서 등의 정보를 기록합니다.
//  => Mock Framework
//     Java: jMock, EasyMock, Mockito, Spock 
//      C++: Google Mock


class SpyTarget : public DLoggerTarget {
	std::vector<std::string> history;

	std::string concat(Level level, const std::string& message) {
		static const char* levelStr[] = {
			"INFO", "WARN", "ERROR",
		};

		return std::string(levelStr[level]) + "@" + message;
	}

public:
	void Write(Level level, const std::string& message) override {
		// 목격한 일을 기록한다.
		history.push_back(concat(level, message));
	}
	
	// 테스트에서 확인할 수 있도록 만들어진 함수
	bool IsReceived(Level level, const std::string& message) {
		return std::find(history.begin(), history.end(), concat(level, message)) != history.end();
	}
};

// DLoggerTarget에 대해서 2개 이상의 타겟을 등록하고, Write 수행하였을 때 
// 모든 Target에 Write가 호출되었는지 여부를 검증하고 싶다.
TEST(DLoggerTest, Write) {
	DLogger logger;
	SpyTarget t1, t2;
	logger.AddTarget(&t1);
	logger.AddTarget(&t2);
	Level test_level = INFO;
	std::string test_message = "test_log_message";

	logger.Write(test_level, test_message);

	EXPECT_TRUE(t1.IsReceived(test_level, test_message));
	EXPECT_TRUE(t2.IsReceived(test_level, test_message));
}
#if 0
TEST(DLoggerTest, Write) {
	DLogger logger;
	FileTarget t1, t2;
	logger.AddTarget(&t1);
	logger.AddTarget(&t2);
	Level test_level = INFO;
	std::string test_message = "test_log_message";

	logger.Write(test_level, test_message);

}
#endif



















