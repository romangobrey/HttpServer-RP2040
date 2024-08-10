#include "Configuration.h"
#include "DeviceModel.h"

Rp2040::DeviceModel Config_DeviceModel = Rp2040::DeviceModel::W5500EvbPico;
unsigned char Config_ServerIp[4] = {192, 168, 1, 170};