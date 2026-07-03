#include "Configuration.h"

using namespace Rp2040;

Rp2040::DeviceModel Configuration::getDeviceModel()
{
    if (SHIELD == "RP2040-ETH")
    {
        return DeviceModel::Rp2040Eth;
    }

    return DeviceModel::W5500EvbPico;
}