#pragma once

namespace Orion {
    namespace Sensors {
        namespace GPS {
            typedef struct {
                float _latitude;
                float _longitude;
                float _altitude;
            } Coordinates;
        }
    }
}