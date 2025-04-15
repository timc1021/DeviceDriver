#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

TEST(DeviceDriver, ReadFromHW) {
	FlashMock mock;
	EXPECT_CALL(mock, read(0xbb))
		.Times(5);

	DeviceDriver driver{ &mock };
	int data = driver.read(0xbb);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}