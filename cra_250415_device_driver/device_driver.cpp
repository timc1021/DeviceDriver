#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int read_value = (int)(m_hardware->read(address));

    for (int i = 0; i < 4; i++) {
        if (read_value != (int)(m_hardware->read(address)))
            throw ReadFailException();
    }

    return read_value;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if (read(address) == 0xff)
        m_hardware->write(address, (unsigned char)data);
    else
        throw WriteFailException();
}