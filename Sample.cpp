
#include <stdio.h>
#include <stdlib.h>


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
	void Setup() override {

	}
#endif

};

int main() {
	abort();

}
