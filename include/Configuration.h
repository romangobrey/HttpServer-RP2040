#pragma once

#include "DeviceModel.h"

namespace Rp2040
{
    class Configuration
    {
    public:
        static constexpr unsigned char serverIp[4] = {192, 168, 1, 170};
        static DeviceModel getDeviceModel();
    };
}
