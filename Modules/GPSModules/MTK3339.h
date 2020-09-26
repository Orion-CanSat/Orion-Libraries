#ifndef __ORION_MODULES_GPSMODULES_MTK3339_H__
#define __ORION_MODULES_GPSMODULES_MTK3339_H__

#include "Orion.h"
#include "Modules/Module.hpp"
#include "Modules/GPSModules/Coordinates.hpp"
#include "Modules/GPSModules/GPS.hpp"

#include "HardwareSerial.h"

#include <stdint.h>
#include <math.h>

namespace Orion
{
    namespace Modules
    {
        namespace GPSModules
        {
            class MTK3339 : virtual public GPS
            {
                public:
                    MTK3339(HardwareSerial* serial);

                    void Update();

                    ~MTK3339();
            };
        }
    }
}

#endif//__ORION_MODULES_GPSMODULES_MTK3339_H__