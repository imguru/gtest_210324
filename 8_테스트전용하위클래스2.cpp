#include <stdio.h>

// SUT
class Engine {
	bool isStart;
public:
	Engine() : isStart(false) {}
	~Engine() {}

	void Start() {
		printf("Engine::Start()\n");
		printf("Engine start...\n");
		isStart = true;
	}

	bool IsStart() const {
		return isStart;
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		// ....
		engine->Start();
		// ....
	}
};

//--------------
#include <gtest/gtest.h>

TEST(CarTest, Go) {
	Engine engine;
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











