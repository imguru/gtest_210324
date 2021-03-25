
#include <gtest/gtest.h>

// 객체의 메모리 누수를 판단하는 목적으로 사용할 수 있습니다.
//   1) 제품 코드에 미리 정의되어야 하는 코드가 있습니다.
//      new / delete 재정의가 필요합니다.
//
//		Image* image1 = new Image;
//		  1) Heap 메모리 생성 - operator new
//		  2) 생성자 호출
//
//		delete image1;
//		  1) 소멸자 호출
//		  2) Heap 메모리 해지 - operator delete
//
//  2) 테스트를 목적으로만 사용될 수 있어야 합니다.
//     -> 조건부 컴파일을 사용하는 방법이 있습니다.

class Image {
public:
#ifdef GTEST_LEAK_TEST
	static int allocCount;

	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		free(p);
		--allocCount;
	}
#endif
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif

void DrawImage() {
	Image* image1 = new Image;
	Image* image2 = new Image;
	Image* image3 = new Image;

	// ...

	delete image1;
	// delete image2;
	// delete image3;
}

class ImageTest : public testing::Test {
protected:
	int alloc;

	ImageTest() : alloc(0) {}

	void SetUp() override {
#ifdef GTEST_LEAK_TEST
		alloc = Image::allocCount;
#endif
	}

	void TearDown() override {
#ifdef GTEST_LEAK_TEST
		int diff = Image::allocCount - alloc;
		EXPECT_EQ(diff, 0) << diff << " Object(s) leaks...";
#endif
	}
};

TEST_F(ImageTest, DrawImage) {
	DrawImage();
}








