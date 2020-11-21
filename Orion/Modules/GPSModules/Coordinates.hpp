#ifndef __ORION_MODULES_GPSMODULES_CORDINATES_H__
#define __ORION_MODULES_GPSMODULES_CORDINATES_H__

#include "Orion.h"

#include <stdint.h>

namespace Orion
{
    namespace Modules
    {
        namespace GPSModules
        {
            typedef struct {
                decPlace _latitude = NAN;
                decPlace _longitude = NAN;
                decPlace _altitude = NAN;
            } Coordinates;
        }
    }
}

#endif//__ORION_MODULES_GPSMODULES_CORDINATES_H__