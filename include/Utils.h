#include <Arduino.h>

namespace Rp2040
{
    class Utils
    {
    public:
        static int char2int(char input);
        static void hex2bin(const char *src, char *target);
        static void generateRp2040MacAddress(uint8_t *macAddress);
    };
}
