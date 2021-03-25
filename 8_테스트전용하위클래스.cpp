#include <stdio.h>

// SUT
class Engine {
public:
	Engine() {}
	virtual ~Engine() {}

	virtual void Start() {
		printf("Engine::Start()\n");
		printf("Engine start...\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		// ....
		// engine->Start();
		// ....
	}
};

//--------------
#include <gtest/gtest.h>

// 테스트 전용 하위 클래스
//  - SUT의 클래스가 테스트를 위한 기능을 제공하고 있지 않다면
//    테스트 코드 안에서 자식 클래스를 통해 해당 기능을 제공하면 됩니다.
//    1) 상속 가능한 클래스로 설계되어 있어야 합니다.
//       => 가상 소멸자
//    2) 함수(기능) 재사용 - 가상 함수 

class TestEngine : public Engine {
	bool isStart;
public:
	TestEngine() : isStart(false) {}

	void Start() override {
		printf("TestEngine::Start()\n");
		Engine::Start();                // 부모의 기능을 그대로 이용한다.
		isStart = true;
	}

	//----
	bool IsStart() const {
		return isStart;
	}
	//----
};

TEST(CarTest, Go) {
	TestEngine engine;
	Car car(&engine);

	car.Go();

	// Engine 객체에 확인할 수 있는 상태가 존재하지 않는다.
	EXPECT_TRUE(engine.IsStart()) << "자동차가 Go 하였을 때";
}

// Car 객체에 Go 함수를 호출하였을 때, Engine의 Start가 제대로 수행되었는지 여부를 검증하고 싶다.
#if 0
TEST(CarTest, Go) {
	Engine engine;
	Car car(&engine);

	car.Go();

	// Engine 객체에 확인할 수 있는 상태가 존재하지 않는다.
}
#endif











