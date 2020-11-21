#include "Orion/Modules/GPSModules/MTK3339.h"

#include <Adafruit_GPS.h>

using namespace Orion::Modules::GPSModules;

MTK3339::MTK3339(HardwareSerial* serial)
{
    _devicePtr = new Adafruit_GPS(serial);
}