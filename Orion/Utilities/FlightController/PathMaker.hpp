#ifndef __ORION_UTILITIES_PATHMAKER_H__
#define __ORION_UTILITIES_PATHMAKER_H__

#include "Orion.h"

#include <stdint.h>
#include <math.h>
#include "Orion/Utilities/FlightController/PathPoint.hpp"

namespace Orion
{
    namespace Utilities
    {
        namespace FlightController
        {
            class PathMaker
            {
            public:
                PathMaker(decPlace refrenceX, decPlace refrenceY, decPlace radius, int circleSteps, decPlace changeDistance);
                void updateRefrence(decPlace refrenceX, decPlace refrenceY);
                decPlace getRefrenceX();
                decPlace getRefrenceY();
                decPlace getRadius();
                int getCircleSteps();
                int getCurrentCircleSteps();
                PathPoint getCurrentPoint();
                PathPoint updatePoint(decPlace distance);
            private:
                decPlace refrenceX;
                decPlace refrenceY;
                decPlace radius;
                decPlace changeDistance;
                int circleSteps;
                int currentCircleStep;
            };
        }
    }
}

#endif //__ORION_UTILITIES_PATHMAKER_H__