#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	FlashMock mock;
	EXPECT_CALL(mock, read(0xbb))
		.Times(5)
		.WillRepeatedly(Return(0));

	DeviceDriver driver{ &mock };
	int data = driver.read(0xbb);
}

TEST(DeviceDriver, WriteHW) {
	FlashMock mock;
	EXPECT_CALL(mock, read(0xbb))
		.Times(5)
		.WillRepeatedly(Return(0xff));
	EXPECT_CALL(mock, write(0xbb, 0x1))
		.Times(1);

	DeviceDriver driver{ &mock };
	driver.write(0xbb, 0x1);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}