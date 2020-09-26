#ifndef __ORION_UTILITIES_FLIGHTCONTROLLER_PID_H__
#define __ORION_UTILITIES_FLIGHTCONTROLLER_PID_H__

#include "Orion.h"

#include <stdint.h>
#include <math.h>

namespace Orion
{
    namespace Utilities
    {
        namespace FlightController
        {
            class PID
            {
            public:
                PID(decPlace P, decPlace I, decPlace D);
                void Update(decPlace error, decPlace dt);
                decPlace GetOutput();
            private:
                decPlace P, I, D;
                decPlace previousError;
                decPlace integral;
                decPlace output;
            };
        }
    }
}

#endif//__ORION_UTILITIES_FLIGHTCONTROLLER_PID_H__