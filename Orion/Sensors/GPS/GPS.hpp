#pragma once

#include <math.h>

#include "Orion/Orion.h"
#include "Orion/Sensors/Sensor.hpp"
#include "Orion/Sensors/GPS/Coordinates.hpp"

namespace Orion {
    namespace Sensors {
        namespace GPS {
            class GPS : public Orion::Sensors::Sensor {
                protected:
                    Coordinates _coordinates;
                
                    uint64_t* GetDataTypes();
                    uint64_t GetDataTypesSize();
                public:
                    GPS();

                    float GetDataType(uint64_t dataType);

                    virtual void Update();

                    virtual bool Send(uint8_t* message, uint64_t len);
                    virtual uint64_t Receive(uint8_t* message, uint64_t len);

                    virtual void Sleep();
                    virtual void WakeUp();

                    virtual void Reset();

                    INLINE static float GetDistance(Coordinates a, Coordinates b) {
                        const uint64_t R = 6371e3;

                        const float phi1 = a._latitude * PI / 180;
                        const float phi2 = b._latitude * PI / 180;

                        const float deltaPhi = (b._latitude - a._latitude) * PI / 180;
                        const float deltaLambda = (b._longitude - a._longitude) * PI / 180;

                        const float alpha = pow(sin(deltaPhi / 2), 2.0) + cos(phi1) * cos(phi2) * pow(sin(deltaLambda / 2), 2.0);
                        const float c = 2 * atan2f(sqrtf(alpha), sqrtf(1 - alpha));

                        return R * c;
                    }
                    INLINE float GetDistance(Coordinates a) {
                        return GPS::GetDistance(this->_coordinates, a);
                    }

                    ~GPS();
            };
        }
    }
}