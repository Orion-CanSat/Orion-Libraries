#ifndef __ORION_UTILITIES_PATHPOINT_H__
#define __ORION_UTILITIES_PATHPOINT_H__

#include "Orion.h"

#include <stdint.h>
#include <math.h>

namespace Orion
{
    namespace Utilities
    {
        namespace FlightController
        {
            class PathPoint
            // Pathpoint describes a path point with the refrence (0, 0) being the landing target.
            {
            public:
                PathPoint(decPlace, decPlace);
                decPlace getX();
                decPlace getY();
                decPlace getPolarAngle();
                decPlace getPolarAngleTo(PathPoint);
            private:
                decPlace x;
                decPlace y;
            };
        }
    }
}

#endif //__ORION_UTILITIES_PATHPOINT_H__