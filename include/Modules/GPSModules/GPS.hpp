#ifndef __ORION_MODULES_GPSMODULES_GPS_H__
#define __ORION_MODULES_GPSMODULES_GPS_H__

#include "Orion.h"
#include "Modules/Module.hpp"
#include "Modules/GPSModules/Coordinates.hpp"

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
                    static decPlace GetDistance(Coordinates& a, Coordinates& b)
                    {
                        const uint64_t R = 6371e3;

                        const decPlace phi1 = a._latitude * PI / 180;
                        const decPlace phi2 = b._latitude * PI / 180;

                        const decPlace deltaPhi = (b._latitude - a._latitude) * PI / 180;
                        const decPlace deltaLambda = (b._longitude - a._longitude) * PI / 180;

                        const decPlace alpha = pow(sin(deltaPhi / 2), 2.0) + cos(phi1) * cos(phi2) * pow(sin(deltaLambda / 2), 2.0);
                        const decPlace c = 2 * atan2f(sqrtf(alpha), sqrtf(1 - alpha));

                        return R * c;
                    }

                    GPS();
            };
        }
    }
}

#endif//__ORION_MODULES_GPSMODULES_GPS_H__