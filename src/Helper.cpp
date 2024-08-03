#include "Helper.h"

using namespace Rp2040;

int Helper::GetCharsSum(String value)
{
    int sum = 0;
    for (int i = 0; i <= value.length(); i++)
    {
        sum += (int)value[i];
    }
    return sum;
}

byte Helper::GenerateMacAddressById(uint id)
{
    String hex;

    srand(id);
    for (int i = 0; i < 6; i++)
    {
        const int tp = rand() % 256;
        hex += tp < 16 ? "0" + tp : "" + tp;
    }
    // byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
}