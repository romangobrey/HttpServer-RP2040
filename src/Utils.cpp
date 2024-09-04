#include "Utils.h"

using namespace Rp2040;

int Utils::char2int(char input)
{
    if (input >= '0' && input <= '9')
    {
        return input - '0';
    }
    if (input >= 'A' && input <= 'F')
    {
        return input - 'A' + 10;
    }
    if (input >= 'a' && input <= 'f')
    {
        return input - 'a' + 10;
    }

    return 0; //  wrong character is detected
}

void Utils::hex2bin(const char *src, char *target)
{
    while (*src && src[1])
    {
        *(target++) = char2int(*src) * 16 + char2int(src[1]);
        src += 2;
    }
}

void Utils::generateRp2040MacAddress(uint8_t *macAddress)
{
    auto chipId = rp2040.getChipID(); // E6625CA563595537

    char bufferTarget[16];
    hex2bin(chipId, bufferTarget);

    auto bytes = reinterpret_cast<uint8_t *>(bufferTarget);
    for (int i = 0; i < 6; i++)
    {
        macAddress[i] = bytes[i + 2]; // 5C A5 63 59 55 37 (cut first 2 bytes)
    }
}
