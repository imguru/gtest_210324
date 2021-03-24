
#include <stdio.h>

class Sample {
public:
	virtual void SetUp() {

	}

};

class Derived : public Sample {
public:
#if 0
	virtual void Setup() {

	}
#endif
	void Setup() override {

	}

};

int main() {

}
