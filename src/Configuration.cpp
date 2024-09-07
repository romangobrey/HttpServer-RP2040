#include "Configuration.h"

using namespace Rp2040;

Rp2040::DeviceModel Configuration::getDeviceModel()
{
    if (SHIELD == "RP2040-ETH")
    {
        return DeviceModel::Rp2040Eth;
    }

    if (SHIELD == "W5500-EVB-Pico")
    {
        return DeviceModel::W5500EvbPico;
    }
}