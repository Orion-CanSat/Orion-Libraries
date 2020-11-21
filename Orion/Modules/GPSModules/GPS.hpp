#ifndef __ORION_MODULES_GPSMODULES_GPS_H__
#define __ORION_MODULES_GPSMODULES_GPS_H__

#include "Orion.h"
#include "Orion/Modules/Module.hpp"
#include "Orion/Modules/GPSModules/Coordinates.hpp"

#include <stdint.h>
#include <math.h>

namespace Orion
{
    namespace Modules
    {
        namespace GPSModules
        {
            class GPS : virtual public Module
            {
                protected:
                    Coordinates _coordinates;

                public:
                    static decPlace GetDistance(Coordinates& a, Coordinates& b);

                    bool HasDataType(uint32_t type);
                    decPlace GetData(uint32_t type);
            };
        }
    }
}

#endif//__ORION_MODULES_GPSMODULES_GPS_H__