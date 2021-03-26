
#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR
};

struct DLoggerTarget {
	virtual DLoggerTarget {};

	virtual void Write(Level level, const std::string& message) = 0;
};

// FileTarget / NetworkTarget / StdoutTarget
class FileTarget : DLoggerTarget {
public:
	void Write(Level level, const std::string& message) override {
		printf("File 기록 - %d(%s)\n", level, message);
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
			e->Write(level, message);
		}
	}
};

//--------------
#include <gtest/gtest.h>


// DLoggerTarget에 대해서 2개 이상의 타겟을 등록하고, Write 수행하였을 때 
// 모든 Target에 Write가 호출되었는지 여부를 검증하고 싶다.
TEST(DLoggerTest, Write) {
	DLogger logger;
	FileTarget t1, t2;
	logger.AddTarget(&t1);
	logger.AddTarget(&t2);
	Level test_level = INFO;
	std::string test_message = "test_log_message";

	logger.Write(test_level, test_message);

}



















