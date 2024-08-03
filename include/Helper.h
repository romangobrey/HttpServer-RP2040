#include <arduino.h>

namespace Rp2040
{
    class Helper
    {
    public:
        static int GetCharsSum(String value);
        static byte GenerateMacAddressById(uint id);
    };
}