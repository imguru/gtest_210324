
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

class Image {
public:
	static int allocCount;

	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		free(p);
		--allocCount;
	}
};

int Image::allocCount = 0;


void DrawImage() {
	Image* image1 = new Image;
	new Image;
	new Image;
	new Image;
	new Image;
	new Image;

	// ...

	// delete image1;
}

class ImageTest : public testing::Test {
protected:
	int alloc;

	ImageTest() : alloc(0) {}

	void SetUp() override {
		alloc = Image::allocCount;
	}

	void TearDown() override {
		int diff = Image::allocCount - alloc;
		EXPECT_EQ(diff, 0) << diff << " Object(s) leaks...";
	}
};

TEST_F(ImageTest, DrawImage) {
	
	DrawImage();

}








